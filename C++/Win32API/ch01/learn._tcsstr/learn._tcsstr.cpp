#include <stdio.h>
#include <Windows.h>
#include <tchar.h>

int main()
{
    TCHAR szStr[] = TEXT("Hello, Windows, Windows API is fun.");
    TCHAR szStrSearch[] = TEXT("Windows");

    _tprintf(TEXT("%s\n"), _tcsstr(szStr, szStrSearch));
}

