#include <stdio.h>
#include <Windows.h>

int main()
{
	char bars[] = "|/-\\";
	int i = 0;
	while (1)
	{
		printf("%c\b", bars[i]);
		i = (i + 1) % 4;
		Sleep(500);
	}

	return 0;
}