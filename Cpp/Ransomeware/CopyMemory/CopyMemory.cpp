#include <Windows.h>
#include <stdio.h>

int main()
{
	char aString1[] = "Hello world";
	char aString2[100];

	printf("aString1: [%s]\n", aString1);
	CopyMemory(aString2, aString1, strlen(aString1) + 1);

	printf("aString2: [%s]\n", aString2);

	return 0;
}