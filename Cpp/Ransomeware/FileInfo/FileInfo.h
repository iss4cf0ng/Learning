#pragma once

#include <Windows.h>
#include <tchar.h>

#define FILETYPE_UNKNOWN 0
#define FILETYPE_EXE_DLL 1
#define FILETYPE_HIGH_PRIORITY 2
#define FILETYPE_LOW_PRIORITY 3
#define FILETYPE_ZIP_TEMP 4
#define FILETYPE_WRITESRC 5
#define FILETYPE_ENCRYPTED 6

#define WZIP_SUFFIX_TEMP _T(".WNCRYT")
#define WZIP_SUFFIX_WRITESRC _T(".WNCYR")
#define WZIP_SUFFIX_CIPHER _T(".WNCRY")

#ifndef BASE_DIRNAME
#define BASE_DIRNAME _T("WANNATRY")
#endif
#ifndef ENCRYPT_ROOT_PATH
// #define ENCRYPT_ROOT_PATH _T("C:\\")
#define ENCRYPT_ROOT_PATH _T("C:\\TESTDATA")
#endif

#ifndef DEBUG
#define DEBUG(fmt, ...) (_tprintf(_T(fmt), __VA_ARGS__))
#else
#define DEBUG(...) (0)
#endif // !DEBUG


struct FileInfo
{
	TCHAR m_szFullPath[360];
	TCHAR m_szName[260];
	LARGE_INTEGER m_cbFileSize;
	DWORD m_dwFileType;
};

typedef FileInfo* PFileInfo;

struct FileNode
{
	FileNode* m_pPrev;
	FileNode* m_pNext;
	FileInfo m_Info;
};

typedef FileNode* PFileNode;

class FileList
{
public:
	PFileNode m_pHead = NULL;
	ULONG m_nFiles = 0;
	FileList();
	~FileList();
	BOOL Insert(PFileNode);
};

typedef FileList* PFileList;