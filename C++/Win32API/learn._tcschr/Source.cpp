#include <stdio.h>
#include <Windows.h>
#include <locale.h>
#include <tchar.h>

int main()
{
	TCHAR szStr[] = TEXT("WindowsAPI�O�̦n��!");
	LPTSTR lp = _tcschr(szStr, TEXT('��'));

	setlocale(LC_ALL, "chs");

	_tprintf(TEXT("szStr����} : %p lp ��} : %p\n"), szStr, lp);
	_tprintf(TEXT("szStr = %s lp = %s\n"), szStr, lp);
}