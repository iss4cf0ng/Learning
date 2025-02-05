#pragma once

#include <Windows.h>
#include <bcrypt.h>
#include <tchar.h>

class EZRSA
{
	BCRYPT_HANDLE m_hProv;
	BCRYPT_KEY_HANDLE m_hKey;

public:
	EZRSA();
	~EZRSA();


	BOOL GenKey();
	
	/// <summary>
	/// Import key from memory.
	/// </summary>
	/// <param name=""></param>
	/// <param name=""></param>
	/// <param name=""></param>
	/// <returns></returns>
	BOOL Import(LPCWSTR, PUCHAR, ULONG);
	/// <summary>
	/// Import key from file.
	/// </summary>
	/// <param name=""></param>
	/// <param name=""></param>
	/// <returns></returns>
	BOOL Import(LPCWSTR, LPCTSTR);

	/// <summary>
	/// Export key to memory.
	/// </summary>
	/// <param name=""></param>
	/// <param name=""></param>
	/// <param name=""></param>
	/// <param name=""></param>
	/// <returns></returns>
	BOOL Export(LPCWSTR, PUCHAR, ULONG, PULONG);
	/// <summary>
	/// Export key to file.
	/// </summary>
	/// <param name=""></param>
	/// <param name=""></param>
	/// <param name=""></param>
	/// <returns></returns>
	BOOL Export(LPCWSTR, LPCTSTR, EZRSA*);

	BOOL Encrypt(PUCHAR, ULONG, PUCHAR, ULONG, PULONG);
	BOOL Decrypt(PUCHAR, ULONG, PUCHAR, ULONG, PULONG);
};

typedef EZRSA* PEZRSA;

BOOL RSAKeyMatch(PEZRSA, PEZRSA);
BOOL RSABlobMatch(PUCHAR, ULONG, PUCHAR, ULONG);
BOOL RSAFileMatch(LPCTSTR, LPCTSTR);

#ifndef  DEBUG
#define DEBUG(fmt, ...) (_tprintf(_T(fmt), __VA_ARGS__))
#else
#define DEBUG(...) (0)
#endif // ! DEBUG