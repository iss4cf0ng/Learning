#include <Windows.h>
#include <stdio.h>

int main()
{
	char aString[] = "Hello world";
	printf("[%s]\n", aString);
	FillMemory(aString, strlen(aString), '@');
	printf("[%s]\n", aString);

	return 0;
}