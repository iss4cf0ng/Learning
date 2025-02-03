#include <Windows.h>
#include <stdio.h>
#include <tchar.h>

#ifdef _DEBUG
#define DEBUG(...) (_ftprintf(stderr, __VA_ARGS__))
#else
#define DEBUG(...) (0)
#endif // _DEBUG


BOOL ReadBuffer(
	LPCTSTR lpFileName,
	LARGE_INTEGER liDistanceToMove,
	DWORD dwMoveMethod,
	PUCHAR pbBuffer,
	ULONG cbBuffer,
	PULONG pcbResult
)
{
	HANDLE hFile;
	LARGE_INTEGER liNewFilePointer;
	BOOL bResult = FALSE;

	if ((hFile = CreateFile(
		lpFileName,
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	)) == INVALID_HANDLE_VALUE)
	{
		DEBUG(_T("open %s fails: %d\n"), lpFileName, GetLastError());
		return FALSE;
	}

	if (!SetFilePointerEx(
		hFile,
		liDistanceToMove,
		&liNewFilePointer,
		dwMoveMethod
	))
	{
		DEBUG(_T("set pointer %s fails: %d\n"), lpFileName, GetLastError());
		goto Error_Exit;
	}

	if (!(bResult = ReadFile(
		hFile,
		pbBuffer,
		cbBuffer,
		pcbResult,
		0
	)))
	{
		DEBUG(_T("Read %s error: %d\n"), lpFileName, GetLastError());
	}

	bResult = TRUE;

Error_Exit:
	CloseHandle(hFile);
	return bResult;
}

BOOL WriteBuffer(
	LPCTSTR lpFileName,
	LARGE_INTEGER ilDistanceToMove,
	DWORD dwMoveMethod,
	PUCHAR pbBuffer,
	ULONG cbBuffer,
	PULONG pcbResult
)
{
	HANDLE hFile;
	LARGE_INTEGER liNewFilePointer;
	BOOL bResult = FALSE;

	if ((hFile = CreateFile(
		lpFileName,
		GENERIC_WRITE,
		FILE_SHARE_READ,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	)) == INVALID_HANDLE_VALUE)
	{
		DEBUG(_T("Open file %s error\n"), lpFileName);
		return FALSE;
	}

	if (!SetFilePointerEx(
		hFile,
		ilDistanceToMove,
		&liNewFilePointer,
		dwMoveMethod
	))
	{
		DEBUG(_T("set pointer %s fails: %d\n"), lpFileName, GetLastError());
		goto Error_Exit;
	}

	if (!(bResult = WriteFile(
		hFile,
		pbBuffer,
		cbBuffer,
		pcbResult,
		0
	)))
	{
		DEBUG(_T("Write %s error\n"), lpFileName);
	}

	bResult = TRUE;

Error_Exit:
	CloseHandle(hFile);
	return bResult;
}

int _tmain(int argc, TCHAR *argv[])
{
	
}