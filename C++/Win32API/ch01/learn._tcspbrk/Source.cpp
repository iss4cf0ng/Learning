#include <stdio.h>
#include <Windows.h>
#include <tchar.h>

int main()
{
	TCHAR szStr[] = TEXT("The 3 men and 2 boys ate 5 pigs.");
	TCHAR szStrCharSet[] = TEXT("0123456789");

	LPTSTR lpSearch = NULL;

	_tprintf(TEXT("1 : %s\n"), szStr);

	lpSearch = _tcspbrk(szStr, szStrCharSet);
	_tprintf(TEXT("2 : %s\n"), lpSearch);

	lpSearch++;
	lpSearch = _tcspbrk(lpSearch, szStrCharSet);
	_tprintf(TEXT("3 : %s\n"), lpSearch);
}