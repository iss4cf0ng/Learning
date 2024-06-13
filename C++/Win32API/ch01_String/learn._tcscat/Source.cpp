#include <tchar.h>
#include <Windows.h>

int main()
{
	TCHAR szStrDest[64] = TEXT("WindowsAPI");
	TCHAR szStrSour[] = TEXT(" is strong!");
	_tcscat_s(szStrDest, _countof(szStrDest), szStrSour);
	_tprintf(TEXT("%s\n"), szStrDest);

	size_t i = _tcslen(szStrDest);
	_tprintf(TEXT("%d\n"), i);
}