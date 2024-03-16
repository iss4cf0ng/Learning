#include <windows.h>
#include <tchar.h>
#include <stdio.h>

BOOL touch(LPCTSTR lpSource, LPCTSTR lpTarget)
{
    HANDLE hFile;
    FILETIME CreationTime, AccessTime, WriteTime;

    //////////////////
    //Get filetime
    //////////////////
    if ((hFile = CreateFile(
        lpSource,
        0,
        FILE_SHARE_READ,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    )) == INVALID_HANDLE_VALUE)
    {
        _tprintf(_T("open file1.txt fails\n"));
        return false;
    }

    //Get file time
    GetFileTime(hFile, &CreationTime, &AccessTime, &WriteTime);

    //Close
    CloseHandle(hFile);

    /////////////////
    //Set filetime
    /////////////////
    if ((hFile = CreateFile(
        lpSource, 
        0, 
        FILE_SHARE_READ, 
        NULL, 
        OPEN_EXISTING, 
        FILE_ATTRIBUTE_NORMAL, 
        NULL)) == INVALID_HANDLE_VALUE)
    {
        _tprintf(_T("open file2.txt fails\n"));
        return false;
    }

    SetFileTime(
        hFile,
        &CreationTime,
        &AccessTime,
        &WriteTime
    );

    //Close
    CloseHandle(hFile);
    return true;
}

int main()
{
    touch(
        _T("C:\\Users\\User\\Desktop\\file1.txt"),
        _T("C:\\TEMP\\file2.txt")
    );

    return 0;
}