; stage2.asm

BITS 16
ORG 0x8000

start:
    cli
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00
    sti

    ; debug message
    mov si, test_msg
    call print

    call clear_screen
    call print_banner

input_loop:
    call newline
    mov si, prompt
    call print

    mov di, buffer

.read:
    xor ah, ah
    int 0x16

    cmp al, 13          ; ENTER
    je .done

    ; echo char
    mov ah, 0x0E
    int 0x10

    stosb
    jmp .read

.done:
    mov al, 0
    stosb

    call newline

    call check_key
    cmp al, 1
    je success

    ; wrong key
    mov si, wrong_msg
    call print
    jmp input_loop

success:
    mov si, success_msg
    call print

hang:
    jmp hang

; -------------------------
; compare buffer with "SECRET"
check_key:
    mov si, buffer
    mov di, correct_key

.compare:
    mov al, [si]
    mov bl, [di]

    cmp al, bl
    jne .fail

    cmp al, 0
    je .ok

    inc si
    inc di
    jmp .compare

.ok:
    mov al, 1
    ret

.fail:
    mov al, 0
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
newline:
    mov ah, 0x0E
    mov al, 13
    int 0x10
    mov al, 10
    int 0x10
    ret

; -------------------------
clear_screen:
    mov ah, 0x00
    mov al, 0x03
    int 0x10
    ret

; -------------------------
print_banner:
    mov si, banner
    call print
    ret

; -------------------------
banner db 13,10
       db "             uu$$$$$$$$$$$uu",13,10
       db "          uu$$$$$$$$$$$$$$$$$uu",13,10
       db "         u$$$$$$$$$$$$$$$$$$$$$u",13,10
       db "        u$$$$$$$$$$$$$$$$$$$$$$$u",13,10
       db "       u$$$$$$$$$$$$$$$$$$$$$$$$$u",13,10
       db "       u$$$$$$*   *$$$*   *$$$$$$u",13,10
       db "       *$$$$*      u$u       $$$$*",13,10
       db "        $$$u       u$u       u$$$",13,10
       db "        $$$u      u$$$u      u$$$",13,10
       db "         *$$$$uu$$$   $$$uu$$$$*",13,10
       db "          *$$$$$$$*   *$$$$$$$*",13,10
       db "            u$$$$$$$u$$$$$$$u",13,10
       db "             u$*$*$*$*$*$*$u",13,10
       db "  uuu        $$u$ $ $ $ $u$$       uuu",13,10
       db "  u$$$$       $$$$$u$u$u$$$       u$$$$",13,10
       db "  $$$$$uu      *$$$$$$$$$*     uu$$$$$$",13,10
       db "u$$$$$$$$$$$uu    *****    uuuu$$$$$$$$$",13,10
       db "$$$$***$$$$$$$$$$uuu   uu$$$$$$$$$***$$$*",13,10
       db " ***      **$$$$$$$$$$$uu **$***",13,10
       db "          uuuu **$$$$$$$$$$uuu",13,10
       db " u$$$uuu$$$$$$$$$uu **$$$$$$$$$$$uuu$$$",13,10
       db " $$$$$$$$$$****           **$$$$$$$$$$$*",13,10
       db "   *$$$$$*                      **$$$$**",13,10
       db "     $$$*                         $$$$*",13,10,13,10

       db "  YOUR FILES ARE ENCRYPTED",13,10
       db "       (Petya style)",13,10,13,10
       db "Press any key to continue...",0

prompt db 13,10,"Key: ",0
wrong_msg db 13,10,"Wrong key! Try again.",0
success_msg db 13,10,"Files were decrypted!",0

correct_key db "PETYA",0
test_msg db 13,10, "here is the test",0

buffer times 32 db 0