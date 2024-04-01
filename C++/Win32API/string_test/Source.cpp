#include <stdlib.h>
#include <stdio.h>
#include <string>

int main()
{
	wchar_t wc = L'A';
	wchar_t str_array[] = L"Hello!";
	wchar_t* pwPtr = str_array;
	wchar_t szwStr[] = L"Hello world!";

	char ch = 'A';
	wchar_t wch = L'A';
	char str[] = "C Language";

	wchar_t wstr[] = L"C Language";
	printf("ch = %d, wch = %d, str = %d, wstr = %d\n", sizeof(ch), sizeof(wch), sizeof(str), sizeof(wstr));

	return 0;
}