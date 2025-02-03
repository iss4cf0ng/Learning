#include "EZRSA.h"
#include "../Common/common.h"
#include <bcrypt.h>

#pragma comment(lib, "BCrypt.lib")

EZRSA::EZRSA()
{
	m_hProv = INVALID_HANDLE_VALUE;
	m_hKey = INVALID_HANDLE_VALUE;
	NTSTATUS status = STATUS_UNSUCCESSFUL;
	if (!NT_SUCCESS(status =
		BCryptOpenAlgorithmProvider(
			&m_hProv,
			BCRYPT_RSA_ALGORITHM,
			NULL,
			0
		)))
	{
		DEBUG("BCryptOpenAlgorithmProvider returns 0x%x\n", status);
		return;
	}

	m_hKey = INVALID_HANDLE_VALUE;
	return;
}

EZRSA::~EZRSA()
{
	if (m_hProv != INVALID_HANDLE_VALUE)
	{
		BCryptCloseAlgorithmProvider(m_hProv, 0);
		m_hProv = INVALID_HANDLE_VALUE;
	}

	if (m_hKey != INVALID_HANDLE_VALUE)
	{
		BCryptDestroyKey(m_hKey);
		m_hKey = INVALID_HANDLE_VALUE;
	}

	return;
}

BOOL EZRSA::GenKey()
{
	NTSTATUS status = STATUS_UNSUCCESSFUL;

	if (!NT_SUCCESS(status =
		BCryptGenerateKeyPair(
			m_hProv,
			&m_hKey,
			2048,
			0
		)))
	{
		DEBUG("BCryptGenerateKeyPair returns 0x%x\n", status);
		return FALSE;
	}

	if (!NT_SUCCESS(status =
		BCryptFinalizeKeyPair(
			m_hKey,
			0
		)))
	{
		DEBUG("BCryptFinalizeKeyPair returns 0x%x\n", status);
		return FALSE;
	}

	return TRUE;
}

BOOL EZRSA::Import(
	LPCWSTR pKeyType,
	PUCHAR pbBlob,
	ULONG cbBlob
)
{
	NTSTATUS status = STATUS_UNSUCCESSFUL;

	if (!NT_SUCCESS(status =
		BCryptImportKeyPair(
			m_hProv,
			NULL,
			pKeyType,
			&m_hKey,
			pbBlob,
			cbBlob,
			0
		)))
	{
		DEBUG("BCryptImportKeyPair returns 0x%x\n", status);
		return FALSE;
	}

	return TRUE;
}

BOOL EZRSA::Import(LPCWSTR pKeyType, LPCTSTR pFileName)
{
	HANDLE hFile = INVALID_HANDLE_VALUE;
	UCHAR abBlob[4096];
	ULONG cbBlob = 0;
	ULONG cbFile;

	NTSTATUS status = STATUS_UNSUCCESSFUL;
	BOOL bResult = TRUE;
	if (INVALID_HANDLE_VALUE == (hFile = CreateFile(
		pFileName,
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	)))
	{
		DEBUG("open %s failed\n", pFileName);
		return FALSE;
	}

	cbFile = GetFileSize(hFile, NULL);
	if (sizeof(abBlob) < cbFile)
	{
		DEBUG("Buffer size %d is not enough for %s\n", (int)sizeof(abBlob), pFileName);
		CloseHandle(hFile);
		return FALSE;
	}

	if (!ReadFile(
		hFile,
		abBlob,
		sizeof(abBlob),
		&cbBlob,
		0
	))
	{
		CloseHandle(hFile);
		DEBUG("Read %s error\n", pFileName);
		return FALSE;
	}

	if (!NT_SUCCESS(status =
		BCryptImportKeyPair(
			m_hProv,
			NULL,
			pKeyType,
			&m_hKey,
			abBlob,
			cbBlob,
			0
		)))
	{
		bResult = FALSE;
	}

	CloseHandle(hFile);

	return bResult;
}

BOOL EZRSA::Export(
	LPCWSTR pKeyType,
	PUCHAR pbBlob,
	ULONG cbBlob,
	PULONG pResult
)
{
	NTSTATUS status = STATUS_UNSUCCESSFUL;
	ULONG cbData;
	if (!NT_SUCCESS(status =
		BCryptExportKey(
			m_hKey,
			NULL,
			pKeyType,
			NULL,
			0,
			&cbData,
			0
		)))
	{
		DEBUG("BCryptExportKey#1 returns 0x%x\n", status);
		return FALSE;
	}

	if (pResult)
	{
		*pResult = cbData;
	}

	if (cbBlob < cbData)
	{
		return FALSE;
	}

	if (!NT_SUCCESS(status =
		BCryptExportKey(
			m_hKey,
			NULL,
			pKeyType,
			pbBlob,
			cbBlob,
			&cbBlob,
			0
		)))
	{
		DEBUG("BCryptExportKey#2 returns 0x%x\n", status);
		return FALSE;
	}

	return TRUE;
}

/// <summary>
/// Export key to file.
/// </summary>
/// <param name="pKeyType"></param>
/// <param name="pFileName"></param>
/// <param name="pEncryptKey"></param>
/// <returns></returns>
BOOL EZRSA::Export(
	LPCWSTR pKeyType,
	LPCWSTR pFileName,
	EZRSA *pEncryptKey
	)
{
	HANDLE hFile = INVALID_HANDLE_VALUE;
	UCHAR abBlob[4096];
	ULONG cbBlob;
	UCHAR abBlock[256];
	ULONG cbData;
	BOOL bResult = TRUE;

	if (!Export(
		pKeyType,
		abBlob,
		sizeof(abBlob),
		&cbBlob
	))
	{
		DEBUG("Export to %s failed\n", pFileName);
		return FALSE;
	}
	
	if (INVALID_HANDLE_VALUE == (hFile = 
		CreateFile(
			pFileName,
			GENERIC_WRITE,
			FILE_SHARE_READ,
			NULL,
			CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			NULL
		)))
	{
		DEBUG("CreateFile %s failed\n", pFileName);
		return FALSE;
	}

	DEBUG("Export %d bytes\n", cbBlob);

	if (pEncryptKey)
	{
		for (
			ULONG i = 0, cbSize = 0, cbBlock = 0;
			i < cbBlob;
			i += cbSize
		)
		{
			cbSize = cbBlob - i;
			if (cbSize > 256 - 11)
			{
				cbSize = 256 - 11;
			}

			if (!pEncryptKey->Encrypt(
				abBlob + i,
				cbSize,
				abBlock,
				sizeof(abBlock),
				&cbBlock
			))
			{
				DEBUG("Encrypt failed\n");
				CloseHandle(hFile);
				return FALSE;
			}

			DEBUG("Export: %d -> %d\n", cbSize, cbBlock);

			if (!WriteFile(
				hFile,
				abBlock,
				cbBlock,
				&cbData,
				0
			) || cbData != cbBlock)
			{
				DEBUG("WriteFile %s failed\n", pFileName);
				CloseHandle(hFile);
				return FALSE;
			}
		}
	}
	else
	{
		if (!WriteFile(
			hFile,
			abBlob,
			cbBlob,
			&cbData,
			0
		))
		{
			DEBUG("WriteFile %s failed\n", pFileName);
			CloseHandle(hFile);
			return FALSE;
		}
	}

	CloseHandle(hFile);
	return TRUE;
}

BOOL EZRSA::Encrypt(
	PUCHAR pbPlain,
	ULONG cbPlain,
	PUCHAR pbCipher,
	ULONG cbCipher,
	PULONG pcbResult
)
{
	NTSTATUS status = STATUS_UNSUCCESSFUL;
	ULONG cbBlock = 2048 / 8;
	ULONG cbMaxEncryptBlock = cbBlock - 11;
	ULONG cbMaxDecryptBlock = cbBlock;
	ULONG cbMaxCipher = (INT)(((cbPlain + cbMaxEncryptBlock - 1) / cbMaxEncryptBlock) * cbBlock);
	ULONG cbData;
	ULONG cbResult = 0;

	if (INVALID_HANDLE_VALUE == m_hKey)
	{
		return FALSE;
	}

	if (!pbCipher && !cbCipher)
	{
		if (pcbResult)
		{
			*pcbResult = cbMaxCipher;
		}

		return TRUE;
	}

	if (cbCipher < cbMaxCipher)
	{
		if (pcbResult)
		{
			*pcbResult = cbMaxCipher;
		}

		DEBUG("EZRSA Encrypt need %d bytes but only %d\n", cbMaxCipher, cbCipher);
		return FALSE;
	}

	cbResult = 0;
	
	for (ULONG i = 0, s = 0; i < cbPlain; i += s)
	{
		s = cbPlain - i;
		if (s > cbMaxEncryptBlock)
		{
			s = cbMaxEncryptBlock;
		}
		if (!NT_SUCCESS(status =
			BCryptEncrypt(
				m_hKey,
				pbPlain + i,
				s,
				NULL,
				NULL,
				0,
				pbCipher + cbResult,
				cbBlock,
				&cbData,
				BCRYPT_PAD_PKCS1
			)))
		{
			DEBUG("BCryptEncrypt returns 0x%x\n", status);
			return FALSE;
		}

		cbResult += cbData;
	}

	if (pcbResult)
	{
		*pcbResult = cbResult;
	}

	return TRUE;
}

BOOL EZRSA::Decrypt(
	PUCHAR pbCipher,
	ULONG cbCipher,
	PUCHAR pbPlain,
	ULONG cbPlain,
	PULONG pcbResult
)
{
	NTSTATUS status = STATUS_UNSUCCESSFUL;
	ULONG cbBlock = 2048 / 8;
	ULONG cbMaxEncryptBlock = cbBlock - 11;
	ULONG cbMaxDecryptBlock = cbBlock;
	ULONG cbMaxPlain = cbCipher / cbBlock * cbMaxEncryptBlock;
	ULONG cbData;
	ULONG cbResult = 0;

	if (INVALID_HANDLE_VALUE == m_hKey)
	{
		return FALSE;
	}

	for (ULONG i = 0; i < cbCipher; i += cbBlock)
	{
		if (!NT_SUCCESS(status =
			BCryptDecrypt(
				m_hKey,
				pbCipher + i,
				cbBlock,
				NULL,
				NULL,
				0,
				pbPlain + cbResult,
				cbBlock,
				&cbData,
				BCRYPT_PAD_PKCS1
			)))
		{
			DEBUG("BCryptDecrypt returns 0x%x\n", status);
			return FALSE;
		}

		cbResult += cbData;
	}

	if (pcbResult)
	{
		*pcbResult = cbResult;
	}

	return TRUE;
}

BOOL RSAKeyMatch(
	PEZRSA Encryptor,
	PEZRSA Decryptor
)
{
	UCHAR TestText[] = "TESTDATA";
	UCHAR abCipher[4096];
	UCHAR abPlain[4096];
	ULONG cbCipher, cbPlain;

	Encryptor->Encrypt(
		TestText, 8,
		abCipher, sizeof(abCipher), &cbCipher
	);

	Decryptor->Decrypt(
		abCipher, cbCipher,
		abPlain, sizeof(abPlain), &cbPlain
	);

	if (cbPlain == 8 && !memcmp(TestText, abPlain, 8))
	{
		return TRUE;
	}

	return FALSE;
}

BOOL RSABlobMatch(
	PUCHAR pbPublicBlob,
	ULONG cbPublicBlob,
	PUCHAR pbPrivateBlob,
	ULONG cbPrivateBlob
)
{
	PEZRSA Encryptor = new EZRSA();
	PEZRSA Decryptor = new EZRSA();

	Encryptor->Import(
		BCRYPT_RSAPUBLIC_BLOB,
		pbPublicBlob,
		cbPublicBlob
	);

	Decryptor->Import(
		BCRYPT_RSAPRIVATE_BLOB,
		pbPrivateBlob,
		cbPrivateBlob
	);

	BOOL bResult = RSAKeyMatch(Encryptor, Decryptor);

	delete Encryptor;
	delete Decryptor;

	return bResult;
}

BOOL RSAFileMatch(
	LPCTSTR PublicFile,
	LPCTSTR PrivateFile
)
{
	PEZRSA Encryptor = new EZRSA();
	PEZRSA Decryptor = new EZRSA();

	Encryptor->Import(BCRYPT_RSAPUBLIC_BLOB, PublicFile);
	Decryptor->Import(BCRYPT_RSAPRIVATE_BLOB, PrivateFile);

	BOOL bResult = RSAKeyMatch(Encryptor, Decryptor);

	delete Encryptor;
	delete Decryptor;

	return bResult;
}