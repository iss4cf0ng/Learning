; peb_walk.asm
; typedef struct _TEB {
;     PVOID Reserved1[12];
;     PPEB  ProcessEnvironmentBlock;  // offset = 12 * 4 = 48 = 0x30
;     PVOID Reserved2[399];
;     BYTE  Reserved3[1952];
;     PVOID TlsSlots[64];
;     BYTE  Reserved4[8];
;     PVOID Reserved5[26];
;     PVOID ReservedForOle;
;     PVOID Reserved6[4];
;     PVOID TlsExpansionSlots;
; } TEB, *PTEB;
;
; typedef struct _PEB {
;     BYTE                          Reserved1[2];
;     BYTE                          BeingDebugged;
;     BYTE                          Reserved2[1];
;     PVOID                         Reserved3[2];
;     PPEB_LDR_DATA                 Ldr;                  // offset = 2+1+1+2*4 = 12 = 0x0C
;     PRTL_USER_PROCESS_PARAMETERS  ProcessParameters;
;     PVOID                         Reserved4[3];
;     PVOID                         AtlThunkSListPtr;     // offset = 0x0C + 4*3 + 8 = 0x0C + 20 = 0x0C + 0x14
;     PVOID                         Reserved5;
;     ULONG                         Reserved6;
;     PVOID                         Reserved7;
;     ULONG                         Reserved8;
;     ULONG                         AtlThunkSListPtr32;
;     PVOID                         Reserved9[45];
;     BYTE                          Reserved10[96];
;     PPS_POST_PROCESS_INIT_ROUTINE PostProcessInitRoutine;
;     BYTE                          Reserved11[128];
;     PVOID                         Reserved12[1];
;     ULONG                         SessionId;
; } PEB, *PPEB;

BITS 32
    mov eax, [fs:0x30]      ; EAX = address of PEB
    mov eax, [eax+0x0C]     ; EAX = PEB->Ldr
    mov eax, [eax+0x14]     ; EAX = Ldr->InMemoryOrderModuleList.Flink, entry[0] = my executable

    mov eax, [eax]          ; EAX = entry[1] = ntdll.dll
    mov eax, [eax]          ; EAX = entry[2] = kernel32.dll
    mov ebx, [eax+0x10]     ; EBX = kernel32 DllBase

    mov eax, ebx
    ret