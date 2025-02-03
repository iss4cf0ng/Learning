#include "hexdump.h"

ULONG hexdump(PUCHAR data, ULONG size)
{
	ULONG nResult = 0;
	for (ULONG i = 0; i < size; i += 16)
	{
		nResult += DEBUG(_T("%08X |"), i);
		for (ULONG j = 0; j < 16; j++)
		{
			if (i + j < size)
			{
				nResult += DEBUG(_T(" %02X"), data[i + j]);
			}
			else
			{
				nResult += DEBUG(_T(" "));
			}

			if ((i + j) % 8 == 0)
			{
				nResult += DEBUG(_T(" "));
			}
		}

		nResult += DEBUG(_T("|"));

		for (ULONG j = 0; j < 16; j++)
		{
			if (i + j < size)
			{
				UCHAR k = data[i + j];
				UCHAR c = k < 32 || k > 127 ? '.' : k;

				nResult += DEBUG(_T("%c"), c);
			}
			else
			{
				nResult += DEBUG(_T(" "));
			}
		}

		nResult += DEBUG(_T("\n"));
	}

	return nResult;
}