#include <stdio.h>
#include <Windows.h>
#include <tchar.h>

#ifdef _DEBUG
#define DEBUG(...) (_ftprintf(stderr, __VA_ARGS__))
#else
#define DEBUG(...) (0)
#endif

ULONG Hexdump(PUCHAR data, ULONG size)
{
    ULONG nResult = 0;
    for (ULONG i = 0; i < size; i += 16)
    {
        printf("%08X |", i);

        nResult += 16;
        for (ULONG j = 0; j < 16; j++)
        {
            if (i + j < size)
            {
                nResult += printf(" %02X", data[i + j]);
            }
            else
            {
                nResult += printf(" 00");
            }
        }

        nResult += printf(" | ");
        for (ULONG j = 0; j < 16; j++)
        {
            if (i + j < size)
            {
                UCHAR k = data[i + j];
                UCHAR c = k < 32 || k > 127 ? '.' : k;
                nResult += printf("%c", c);
            }
            else
            {
                nResult += printf(" ");
            }
        }

        nResult += printf("\n");
    }

    return nResult;
}

BOOL ReadBuffer(
    LPCTSTR lpFileName,
    PUCHAR* ppBuffer,
    PULONG pcbResult
)
{
    HANDLE hFile;
    LARGE_INTEGER fileSize;
    DWORD bytesRead = 0;
    BOOL bResult = FALSE;

    *ppBuffer = NULL;

    if ((hFile = CreateFile(
        lpFileName,
        GENERIC_READ,
        FILE_SHARE_READ,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    )) == INVALID_HANDLE_VALUE)
    {
        _tprintf(_T("CreateFile() failed: %d\n"), GetLastError());
        return FALSE;
    }

    if (!GetFileSizeEx(hFile, &fileSize)) 
    {
        _tprintf(_T("GetFileSizeEx() failed: %d\n"), GetLastError());
        goto Error_Exit;
    }

    *ppBuffer = new UCHAR[(ULONG)fileSize.QuadPart];
    if (*ppBuffer == NULL) 
    {
        _tprintf(_T("Failed to allocate memory.\n"));
        goto Error_Exit;
    }

    if (!ReadFile(hFile, *ppBuffer, (DWORD)fileSize.QuadPart, &bytesRead, NULL)) 
    {
        _tprintf(_T("ReadFile() failed: %d\n"), GetLastError());
        delete[] * ppBuffer;
        *ppBuffer = NULL;
        goto Error_Exit;
    }

    *pcbResult = bytesRead;
    bResult = TRUE;

Error_Exit:
    CloseHandle(hFile);
    return bResult;
}

int _tmain(int argc, TCHAR* argv[])
{
    if (argc < 2) 
    {
        _tprintf(_T("Usage: %s <file_name>\n"), argv[0]);
        return 1;
    }

    LPCTSTR fileName = argv[1];
    PUCHAR buffer = NULL;
    ULONG bytesRead = 0;

    if (ReadBuffer(fileName, &buffer, &bytesRead)) 
    {
        _tprintf(_T("Read %lu bytes from the file:\n"), bytesRead);
        Hexdump(buffer, bytesRead);
        delete[] buffer;
    }
    else 
    {
        _tprintf(_T("Failed to read the file.\n"));
    }

    return 0;
}