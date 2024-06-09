#include <Windows.h>
#include <stdio.h>
#include <tchar.h>
#include <locale.h>

int compare(const void* arg1, const void* arg2);

int main()
{
	setlocale(LC_ALL, "chs");

	LPCTSTR arrStr[] = {
		TEXT("�n�ݪ��F��.avi"),
		TEXT("�������t��.avi"),
		TEXT("�ǲ߸��"),
		TEXT("�@�~"),
	};
	qsort(arrStr, _countof(arrStr), sizeof(LPTSTR), compare);

	for (int i = 0; i < _countof(arrStr); i++)
		_tprintf(TEXT("%s\n"), arrStr[i]);

	return 0;
}

int compare(const void* arg1, const void* arg2)
{
	return _tcscoll(*(LPTSTR*)arg1, *(LPTSTR*)arg2);
}