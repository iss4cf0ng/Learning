#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
	char aString[] = "Hello, world";
	char* pString = NULL;
	int slen = strlen(aString);
	printf("aString: [%s]\n", aString);
	pString = (char*)HeapAlloc(
		GetProcessHeap(),
		0,
		slen + 1
	);

	if (pString == NULL)
	{
		printf("HeapAlloc() error\n");
		return 0;
	}

	strcpy_s(pString, slen + 1, aString);
	printf("pString: [%s]\n", pString);

	HeapFree(GetProcessHeap(), 0, pString);

	return 0;
}