; dynamic.asm

BITS 32
    call main ; skip string table

; string table
s_loadlib:  db "LoadLibraryA", 0        ; offset 0
s_user32:   db "user32.dll", 0          ; offset = length of LoadLibraryA + termination char = 13
s_msgbox:   db "MessageBoxA", 0         ; offset = 13 + length of user32.dll + termination char = 13 + 11 = 24
s_text:     db "Hello from test 5!", 0  ; offset = 24 + length of MessageBoxA + termination char = 36
s_caption:  db "Full PIC shellcode", 0  ; offset = 36 + length of previous string + termination char = 36 + 19 = 55

main:
    pop ebp ; EBP = base of string table

    ; PEB walk -> kernel32 base -> EBX
    mov eax, [fs:0x30]
    mov eax, [eax + 0x0C]
    mov eax, [eax + 0x14]
    mov eax, [eax]
    mov eax, [eax]
    mov ebx, [eax + 0x10] ; kernel32 base

    ; export parse -> GetProcAddress -> ESI
    mov edx, [ebx + 0x3C]
    add edx, ebx
    mov edx, [edx + 0x78]
    add edx, ebx

    mov ecx, [edx + 0x18]
    mov edi, [edx + 0x20]
    add edi, ebx

.find_gpa:
    dec ecx
    mov eax, [edi + ecx*4]              ; next address
    add eax, ebx

    cmp dword [eax], 0x50746547         ; "GetP"
    jne .find_gpa

    cmp dword [eax + 4], 0x41636F72     ; "rocA"
    jne .find_gpa

    cmp dword [eax + 8], 0x65726464     ; "ddre"
    jne .find_gpa

    mov edi, [edx + 0x24]
    add edi, ebx
    movzx ecx, word [edi + ecx * 2]
    mov edi, [edx + 0x1C]
    add edi, ebx
    mov eax, [edi + ecx * 4]
    add eax, ebx
    mov esi, eax

    ; GetProcAddress(kernel32, "LoadLibraryA")
    lea eax, [ebp + 0]                  ; EAX = "LoadLibraryA"
    push eax
    push ebx                            ; kernel32 base
    call esi                            ; GetProcAddress(kernel32, "LoadLibraryA")
    mov ecx, eax                        ; ECX = LoadLibraryA

    ; LoadLibraryA("user32.dll")
    lea eax, [ebp + 13]                 ; EAX = "user32.dll"
    push eax                            ; push address of "user32.dll" into stack as a parameter
    call ecx                            ; LoadLibrary("user32.dll")
    mov edi, eax                        ; EDI = user32 base

    ; GetProcAddress(user32, "MessageBoxA")
    lea eax, [ebp + 24]                 ; EAX = "MessageBoxA"
    push eax
    push edi                            ; user32 base
    call esi                            ; GetProcAddress(user32, "MessageBoxA")

    ; MessageBoxA(NULL, text, caption, MB_OK)
    push 0                              ; uType = MB_OK
    lea ecx, [ebp + 55]
    push ecx                            ; lpCaption
    lea ecx, [ebp + 36]
    push ecx                            ; lpText
    push 0                              ; hWnd
    call eax                            ; MessageBoxA()

    ret