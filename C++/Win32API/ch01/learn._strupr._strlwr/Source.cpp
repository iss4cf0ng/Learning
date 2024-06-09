#include <Windows.h>
#include <stdio.h>
#include <tchar.h>

#pragma error disable C4996

int main()
{
	TCHAR szStr[] = TEXT("Windows API is strong!");
	_tprintf(TEXT("%s\n"), _tcsupr(szStr));
	_tprintf(TEXT("%s\n"), _tcslwr(szStr));
}