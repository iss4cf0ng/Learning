#include <tchar.h>
#include <Windows.h>
#include <strsafe.h>

int main()
{
	TCHAR szStrDest[64];
	TCHAR szStrSour[] = TEXT("brainless fool");
	//_tcscpy(szStrDest, szStrSour);
	_tcscpy_s(szStrDest, _countof(szStrDest), szStrSour);
	_tprintf(TEXT("%s\n"), szStrDest);

	TCHAR szResType[128] = { 0 };
	//_tcscpy_s(szResType, 5, szStrSour);
	StringCchCopy(szResType, 5, szStrSour);
	_tprintf(TEXT("%s\n"), szResType);
}