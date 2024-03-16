#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <tchar.h>

#define DEBUG(...) (fprintf(stderr, __VA_ARGS__))

BOOL error_exit(HANDLE hFile, BOOL bResult)
{
    CloseHandle(hFile);
    return bResult;
}

BOOL ReadBuffer(
    LPCTSTR lpFileName,
    LARGE_INTEGER liDistance2Move,
    DWORD dwMoveMethod,
    PUCHAR pbBuffer,
    ULONG cbBuffer,
    PULONG pcbResult
)
{
    HANDLE hFile;
    LARGE_INTEGER liNewFile2Pointer;
    BOOL bResult = FALSE;

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
        DEBUG("open %s fails: %d\n", lpFileName, GetLastError());
        return false;
    }

    if (!SetFilePointerEx(
        hFile,
        liDistance2Move,
        &liNewFile2Pointer,
        dwMoveMethod
    ))
    {
        DEBUG("set pointer %s fails: %d\n", lpFileName, GetLastError());
        return error_exit(hFile, bResult);
    }

    if (!(bResult = ReadFile(
        hFile,
        pbBuffer,
        cbBuffer,
        pcbResult,
        0
    )))
    {
        DEBUG("Read %s error: %d\n", lpFileName, GetLastError());
    }
    bResult = TRUE;
}

BOOL WriteBuffer(
    LPCTSTR lpFileName,
    LARGE_INTEGER liDistance2Move,
    DWORD dwMoveMethod,
    PUCHAR pbBuffer,
    ULONG cbBuffer,
    PULONG pcbResult
)
{
    HANDLE hFile;
    LARGE_INTEGER liNewFilePointer;
    BOOL bResult = FALSE;

    if ((hFile = CreateFile(
        lpFileName,
        GENERIC_WRITE,
        FILE_SHARE_READ,
        NULL,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    )) == INVALID_HANDLE_VALUE)
    {
        DEBUG("Open file %s error\n", lpFileName);
        return FALSE;
    }

    if (!SetFilePointerEx(
        hFile,
        liDistance2Move,
        &liNewFilePointer,
        dwMoveMethod
    ))
    {
        DEBUG("Set pointer %s fails: %d\n", lpFileName, GetLastError());
        error_exit(hFile, bResult);
    }

    if (!(bResult = WriteFile(
        hFile,
        pbBuffer,
        cbBuffer,
        pcbResult,
        0
    )))
    {
        DEBUG("Write %s error\n", lpFileName);
    }
    bResult = TRUE;
}

int main()
{

}