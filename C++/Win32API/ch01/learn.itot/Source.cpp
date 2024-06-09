#include <iostream>
#include <Windows.h>
#include <tchar.h>
#include <locale.h>

int compare(const void* arg1, const void* arg2);

int main()
{
	int n = 0x12CFFE20;
	TCHAR szBuf[16] = { 0 };

	_itot_s(n, szBuf, _countof(szBuf), 10);
	_tprintf(TEXT("%s\n"), szBuf);
	_itot_s(n, szBuf, _countof(szBuf), 16);
	_tprintf(TEXT("%s\n"), szBuf);

	setlocale(LC_ALL, "chs");

	LPCTSTR arrStr[] = {
		TEXT("4. 原理.avi"),
		TEXT("5. 複習.avi"),
		TEXT("6. 電腦.avi"),
		TEXT("2. 手機.avi"),
		TEXT("1. 作業.avi"),
		TEXT("3. 書本.avi"),
	};
	qsort(arrStr, _countof(arrStr), sizeof(LPCTSTR), compare);

	for (int i = 0; i < _countof(arrStr); i++)
		_tprintf(TEXT("%s\n"), arrStr[i]);

	return 0;
}

int compare(const void* arg1, const void* arg2)
{
	LPTSTR p1 = NULL;
	LPTSTR p2 = NULL;
	double d1 = _tcstod(*(LPTSTR *)arg1, &p1);
	double d2 = _tcstod(*(LPTSTR *)arg2, &p2);

	if (d1 != d2)
	{
		if (d1 > d2)
			return 1;
		else
			return -1;
	}
}