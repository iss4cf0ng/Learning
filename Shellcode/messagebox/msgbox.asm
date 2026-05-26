; msgbox.asm
; Memory layout:
;
;   +----------------------+
;   | call msgbox          |
;   +----------------------+
;   | str_msg              |
;   | "Hello world..." \0  |
;   +----------------------+
;   | str_cap              |
;   | "Test 2" \0          |
;   +----------------------+
;   | msgbox:              |
;   | pop esi              |
;   | ...                  |
;   +----------------------+

BITS 32
    call shellcode_entry

str_msg: db "Hello world from msgbox.asm", 0        ; 27 chars + 1 null char = 28 chars = 28 bytes
str_cap: db "Test 2", 0                             ; 6 chars + 1 null char = 7 bytes

STR_CAP_OFFSE equ str_cap - str_msg                 ; compute relative offset automatically = &str_cap - &str_msg

shellcode_entry:
    pop esi                         ; esi = runtime address of str_msg = &str_msg

    ; MessageBoxA(NULL, str_msg, str_cap, MB_OK)
    ; Pushing parameters from right to left
    ; https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-messageboxa#parameters
    push 0                          ; uType = MB_OK
    lea eax, [esi+STR_CAP_OFFSE]    ; eax = &str_cap
    push eax                        ; lpCaption (str_cap)
    push esi                        ; lpText (str_msg)
    push 0                          ; hWnd = NULL

    mov eax, 0xDEADBEEF ; MessageBoxA exported addr: sentinel, patched by loader
    call eax

    ret