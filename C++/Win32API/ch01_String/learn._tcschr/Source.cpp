#include <stdio.h>
#include <Windows.h>
#include <locale.h>
#include <tchar.h>

int main()
{
	TCHAR szStr[] = TEXT("WindowsAPI是最好的!");
	LPTSTR lp = _tcschr(szStr, TEXT('最'));

	setlocale(LC_ALL, "chs");

	_tprintf(TEXT("szStr的位址 : %p lp 位址 : %p\n"), szStr, lp);
	_tprintf(TEXT("szStr = %s lp = %s\n"), szStr, lp);
}