#include <Windows.h>
#include <stdio.h>

int main()
{
	DWORD drivers = GetLogicalDrives();
	CHAR root[4] = "A:";
	for (int i = 0; i < 26; i++)
	{
		if (drivers & (1 << i))
		{
			root[0] = i + 'A';
			printf("Driver %c: found, type: %d\n", i + 'A', GetDriveTypeA(root));
		}
	}
}