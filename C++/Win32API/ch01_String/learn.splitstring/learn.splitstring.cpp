#include <iostream>
#include <Windows.h>
#include <tchar.h>

int main()
{
	TCHAR strToken[] = TEXT("A string\tof ,,tokens\nand some more tokens");
	TCHAR strDelimit[] = TEXT(" ,\t\n");
	
	LPTSTR lpToken = NULL;
	LPTSTR lpTokenNext = NULL;

	lpToken = _tcstok_s(strToken, strDelimit, &lpToken);

	while (lpToken != NULL)
	{
		_tprintf(TEXT("%s\n"), lpToken);
		lpToken = _tcstok_s(NULL, strDelimit, &lpTokenNext);
	}
}