#include <Windows.h>
#include <stdio.h>
#include <tchar.h>
#include <strsafe.h>

void DisplayErrorBox(LPCTSTR lpszFunction);
int Traverse(LPCTSTR pDirName)
{
	WIN32_FIND_DATA ffd;
	LARGE_INTEGER filesize;
	TCHAR szDir[MAX_PATH];
	size_t length_of_arg;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	DWORD dwError = 0;

	StringCchLength(pDirName, MAX_PATH, &length_of_arg);

	if (length_of_arg > (MAX_PATH - 3))
	{
		_tprintf(TEXT("Directory path is too long\n"));
		return -1;
	}

	_tprintf(TEXT("Target directory is %s\n"), pDirName);

	StringCchCopy(szDir, MAX_PATH, pDirName);
	StringCchCat(szDir, MAX_PATH, TEXT("\\*"));

	hFind = FindFirstFile(szDir, &ffd);

	if (INVALID_HANDLE_VALUE == hFind)
	{
		DisplayErrorBox(TEXT("FindFirstFile"));
		return dwError;
	}

	do
	{
		if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			_tprintf(TEXT("%s <DIR>\n"), ffd.cFileName);
		}
		else
		{
			filesize.LowPart = ffd.nFileSizeLow;
			filesize.HighPart = ffd.nFileSizeHigh;
			_tprintf(TEXT("%s %ld bytes\n"), ffd.cFileName, filesize.QuadPart);
		}
	} while (FindNextFile(hFind, &ffd) != 0);

	dwError = GetLastError();
	if (dwError != ERROR_NO_MORE_FILES)
	{
		DisplayErrorBox(TEXT("FindFirstFile"));
	}

	FindClose(hFind);

	//////////////////////
	// Traverse
	//////////////////////

	StringCchCopy(szDir, MAX_PATH, pDirName);
	StringCchCat(szDir, MAX_PATH, TEXT("\\*"));
	hFind = FindFirstFile(szDir, &ffd);

	if (INVALID_HANDLE_VALUE == hFind)
	{
		DisplayErrorBox(TEXT("FindFirstFile"));
		return dwError;
	}

	do
	{
		if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if (!_tcsicmp(ffd.cFileName, _T(".")) || !_tcsicmp(ffd.cFileName, _T("..")))
			{
				continue;
			}

			StringCchLength(pDirName, MAX_PATH, &length_of_arg);
			if (length_of_arg > (MAX_PATH - 3 - _tcslen(ffd.cFileName)))
			{
				_tprintf(TEXT("Directory path is too long.\n"));
				return -1;
			}

			StringCchCopy(szDir, MAX_PATH, pDirName);
			StringCchCat(szDir, MAX_PATH, _T("\\"));
			StringCchCat(szDir, MAX_PATH, ffd.cFileName);

			Traverse(szDir);
		}

	} while (FindNextFile(hFind, &ffd) != 0);

	dwError = GetLastError();
	if (dwError != ERROR_NO_MORE_FILES)
	{
		DisplayErrorBox(TEXT("FindFirstFile"));
	}

	FindClose(hFind);
	
	return dwError;
}

int _tmain(int argc, TCHAR* argv[])
{
	DWORD drivers = GetLogicalDrives();
	TCHAR root[4] = _T("A:\\");
	for (int i = 0; i < 26; i++)
	{
		if (drivers & (1 << i))
		{
			root[0] = i + _T('A');
			_tprintf(_T("Driver %c: found, type %d\n"), i + _T('A'), GetDriveType(root));
			Traverse(root);
		}
	}

	return 0;
}

void DisplayErrorBox(LPCTSTR lpszFunction)
{
	LPVOID lpMsgBuf;
	LPVOID lpDisplayBuf;
	DWORD dw = GetLastError();

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		dw,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf,
		0,
		NULL
	);

	lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT,
		(lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR));
	StringCchPrintf((LPTSTR)lpDisplayBuf,
		LocalSize(lpDisplayBuf) / sizeof(TCHAR),
		TEXT("%s failed with error %d: %s"),
		lpszFunction, dw, lpMsgBuf);
	MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);

	LocalFree(lpMsgBuf);
	LocalFree(lpDisplayBuf);
}