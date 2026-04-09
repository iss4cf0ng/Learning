BITS 16
ORG 0x7C00

start:
    call clear_screen
    call print_banner

    ; wait any key
    xor ah, ah
    int 0x16

    call clear_screen
    call ask_key

hang:
    jmp hang

; -------------------------
clear_screen:
    mov ah, 0x00
    mov al, 0x03
    int 0x10
    ret

; -------------------------
print:
.next:
    lodsb
    cmp al, 0
    je .done

    mov ah, 0x0E
    int 0x10
    jmp .next

.done:
    ret

; -------------------------
print_banner:
    mov si, banner
    call print
    ret

; -------------------------
ask_key:
    mov si, prompt
    call print

    mov di, buffer

.read:
    xor ah, ah
    int 0x16

    cmp al, 13      ; Enter
    je .done

    ; echo
    mov ah, 0x0E
    int 0x10

    stosb
    jmp .read

.done:
    mov al, 0
    stosb

    ; newline
    mov ah, 0x0E
    mov al, 13
    int 0x10
    mov al, 10
    int 0x10

    mov si, result
    call print

    mov si, buffer
    call print

    ret

; -------------------------
banner db 13,10
       db "  YOUR FILES ARE ENCRYPTED",13,10
       db "       (Petya style)",13,10,13,10
       db "Press any key to continue...",0

prompt db 13,10,"Enter key: ",0
result db 13,10,"You entered: ",0

buffer times 32 db 0

times 510 - ($ - $$) db 0
dw 0xAA55