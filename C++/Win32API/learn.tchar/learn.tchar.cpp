#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include <windows.h>
#include <winnt.h>

int main()
{
    CHAR str[] = "C語言";
    WCHAR wstr[] = L"C語言";
    TCHAR szStr[] = TEXT("C語言");

    _tprintf(TEXT("strlen(str) = %d, wcslen(wstr) = %d\n"), strlen(str), wcslen(wstr));
    _tprintf(TEXT("_tcslen(str) = %d\n"), _tcslen(szStr));
}