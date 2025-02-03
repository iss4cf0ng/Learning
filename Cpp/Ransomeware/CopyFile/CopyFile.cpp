#include <Windows.h>
#include <tchar.h>

int main()
{
	if (!CopyFile(
		_T("D:\\url.txt"),
		_T("D:\\url_copy.txt"),
		FALSE
	))
	{
		_tprintf(_T("CopyFile() error: %d\n", GetLastError()));
		return FALSE;
	}
}