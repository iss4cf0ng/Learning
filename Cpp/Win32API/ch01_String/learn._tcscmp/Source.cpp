#include <Windows.h>
#include <tchar.h>
#include <locale.h>

int main()
{
	TCHAR szStr1[] = TEXT("ABCDE"); //ASCII of E : 0x45
	TCHAR szStr2[] = TEXT("ABCDe"); //ASCII of e : 0x65

	int n = _tcscmp(szStr1, szStr2);
	if (n > 0)
		_tprintf(TEXT("szStr1 > szStr2"));
	else if (n == 0)
		_tprintf(TEXT("szStr1 = szStr2"));
	else
		_tprintf(TEXT("szStr1 < szStr2"));

	_tprintf(TEXT("\n"));
	setlocale(LC_ALL, "chs");
	TCHAR szStr3[] = TEXT("你好");
	TCHAR szStr4[] = TEXT("你你好");

	n = _tcscmp(szStr3, szStr4);
	if (n > 0)
		_tprintf(TEXT("szStr1 > szStr2"));
	else if (n == 0)
		_tprintf(TEXT("szStr1 = szStr2"));
	else
		_tprintf(TEXT("szStr1 < szStr2"));

	_tprintf(TEXT("\n"));
	n = _tcscoll(szStr3, szStr4);
	if (n > 0)
		_tprintf(TEXT("szStr1 > szStr2"));
	else if (n == 0)
		_tprintf(TEXT("szStr1 = szStr2"));
	else
		_tprintf(TEXT("szStr1 < szStr2"));
}