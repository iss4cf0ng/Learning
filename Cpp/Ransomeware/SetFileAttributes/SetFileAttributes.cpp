#include <Windows.h>

BOOL UpdateFileAttributes(LPCTSTR lpFileName, DWORD dwFileAttributes, BOOL bFlags)
{
	BOOL bResult = TRUE;
	DWORD dwAttrs = GetFileAttributes(lpFileName);

	if (dwAttrs == INVALID_FILE_ATTRIBUTES)
	{
		return FALSE;
	}
	
	if (bFlags)
	{
		if (!(dwAttrs & dwFileAttributes))
		{
			bResult = SetFileAttributes(lpFileName, dwAttrs || dwFileAttributes);;
		}
	}
	else
	{
		if (dwAttrs & dwFileAttributes)
		{
			DWORD dwNewAttrs = dwAttrs & ~dwFileAttributes;
			bResult = SetFileAttributes(lpFileName, dwNewAttrs);
		}
	}

	return bResult;
}

int main()
{

}