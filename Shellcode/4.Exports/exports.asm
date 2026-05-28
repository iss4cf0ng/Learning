; exports.asm
; Procedure:
;   1. PEB walk
;   2. kernel32 base
;   3. parse exports
;   4. find GetProcAddress
;   5. return GetProcessAddress VA in EAX

BITS 32
    mov eax, [fs:0x30]
    mov eax, [eax+0x0C]
    mov eax, [eax+0x14]
    mov eax, [eax]
    mov eax, [eax]
    mov ebx, [eax + 0x10]

    mov edx, [ebx+0x3C]
    add edx, ebx
    
    mov edx, [edx+0x78]
    add edx, ebx

    mov ecx, [edx+0x18]
    mov edi, [edx+0x20]
    add edi, ebx

find_name:
    dec ecx
    mov esi, [edi+ecx*4]
    add esi, ebx

    ; Compare first 4 bytes: "GetP" = 0x50746547
    mov eax, [esi]
    cmp eax, 0x50746547
    jne find_name

    ; Compare next 4 bytes: "rocA" = 0x41636F72
    mov eax, [esi+4]
    cmp eax, 0x41636F72
    jne find_name

    ; Compare next 4 bytes: "ddre" = 0x65726464
    mov eax, [esi+8]
    cmp eax, 0x65726464
    jne find_name

    ; Found!

    mov esi, [edx + 0x24]
    add esi, ebx
    movzx ecx, word [esi + ecx*2]

    ; get function RVA
    mov esi, [edx + 0x1C]
    add esi, ebx
    mov eax, [esi + ecx*4]
    add eax, ebx

    ret