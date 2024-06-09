#include <tchar.h>
#include <Windows.h>

int main()
{
	TCHAR szStr[] = TEXT("Hello, WIndows, WIndows API program is string!");
	for (size_t i = 0; i < _tcslen(szStr); i++)
	{
		_tprintf(TEXT("%c"), _totupper(szStr[i]));
	}
	_tprintf(TEXT("\n"));

	for (size_t i = 0; i < _tcslen(szStr); i++)
	{
		_tprintf(TEXT("%c"), _totlower(szStr[i]));
	}
	_tprintf(TEXT("\n"));
}