; =========================
; stage2.asm (Salsa20 mini FDE)
; =========================

BITS 16
ORG 0x8000

start:
    cli
    mov ax, 0x0800
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x9C00
    sti

    call clear_screen
    mov si, banner
    call print

input_loop:
    call newline
    mov si, prompt
    call print

    mov di, buffer

.read:
    xor ah, ah
    int 16h
    cmp al, 13
    je .done

    mov ah, 0x0E
    mov al, '*'
    int 10h

    stosb
    jmp .read

.done:
    mov al, 0
    stosb
    call newline

    call read_metadata
    call derive_key
    call salsa_init
    call decrypt_verifier
    call check_verifier

    cmp al, 1
    jne wrong

    mov si, success_msg
    call print

    call decrypt_disk
    call chainload

wrong:
    mov si, wrong_msg
    call print
    jmp input_loop

; =========================
; READ METADATA
; =========================
read_metadata:
    mov si, dap
    mov word [si+2], 1
    mov dword [si+4], buffer_disk
    mov word [si+8], 0x0800
    mov dword [si+10], 2048

    mov ah, 42h
    mov dl, 80h
    int 13h

    mov si, buffer_disk
    add si, 8

    mov di, salt
    mov cx, 8
    rep movsb

    mov di, verifier_enc
    mov cx, 16
    rep movsb

    ret

; =========================
; KEY DERIVATION
; =========================
derive_key:
    xor bx, bx
    mov si, buffer

.pw:
    lodsb
    cmp al, 0
    je .salt
    add bl, al
    jmp .pw

.salt:
    mov si, salt
    mov cx, 8
.sloop:
    lodsb
    add bl, al
    loop .sloop

    mov [key], bl
    ret

; =========================
; SALSA INIT (simple key schedule)
; =========================
salsa_init:
    mov si, key
    mov di, salsa_state
    mov cx, 16
.fill:
    mov al, [si]
    stosb
    loop .fill
    ret

; =========================
; SALSA BLOCK (8 rounds)
; =========================
salsa_block:
    push cx si di

    mov cx, 8

.round:
    ; quarter round
    mov al, [salsa_state]
    add al, [salsa_state+1]
    rol al, 7
    mov [salsa_state], al

    mov al, [salsa_state+2]
    xor al, [salsa_state]
    rol al, 9
    mov [salsa_state+2], al

    loop .round

    ; output → buffer
    mov si, salsa_state
    mov di, salsa_buf
    mov cx, 64
.rep:
    mov al, [si]
    stosb
    inc si
    loop .rep

    pop di si cx
    ret

; =========================
; DECRYPT VERIFIER
; =========================
decrypt_verifier:
    call salsa_block

    mov cx, 16
    mov si, verifier_enc
    mov di, verifier_buf
    mov bx, salsa_buf

.loop:
    mov al, [si]
    xor al, [bx]
    mov [di], al

    inc si
    inc di
    inc bx
    loop .loop

    ret

; =========================
; CHECK
; =========================
check_verifier:
    mov si, verifier_buf
    mov di, expected

.loop:
    mov al, [si]
    mov bl, [di]

    cmp al, bl
    jne .fail
    cmp al, 0
    je .ok

    inc si
    inc di
    jmp .loop

.ok:
    mov al, 1
    ret

.fail:
    mov al, 0
    ret

; =========================
; DECRYPT DISK
; =========================
decrypt_disk:
    mov cx, 20
    mov si, 2049

.next:
    push cx si

    mov word [dap+2], 1
    mov dword [dap+4], buffer_disk
    mov word [dap+8], 0x0800
    mov dword [dap+10], si

    mov ah, 42h
    mov dl, 80h
    mov si, dap
    int 13h

    call salsa_block

    mov cx, 512
    mov di, buffer_disk
    mov bx, salsa_buf

.xor:
    mov al, [di]
    xor al, [bx]
    mov [di], al

    inc di
    inc bx
    cmp bx, salsa_buf+64
    jne .ok

    call salsa_block
    mov bx, salsa_buf

.ok:
    loop .xor

    mov ah, 43h
    mov dl, 80h
    mov si, dap
    int 13h

    pop si cx
    inc si
    loop .next
    ret

; =========================
; CHAINLOAD
; =========================
chainload:
    mov word [dap+2], 1
    mov dword [dap+4], 0x7C00
    mov word [dap+8], 0
    mov dword [dap+10], 2049

    mov ah, 42h
    mov dl, 80h
    mov si, dap
    int 13h

    jmp 0x0000:0x7C00

; =========================
; UTILS
; =========================
print:
    lodsb
    cmp al, 0
    je .done
    mov ah, 0x0E
    int 10h
    jmp print
.done:
    ret

newline:
    mov ah,0x0E
    mov al,13
    int 10h
    mov al,10
    int 10h
    ret

clear_screen:
    mov ah,0
    mov al,3
    int 10h
    ret

; =========================
; DATA
; =========================
banner db "Mini Salsa20 Boot",0
prompt db 13,10,"Password: ",0
wrong_msg db 13,10,"Wrong!",0
success_msg db 13,10,"Decrypting...",0

expected db "BOOT_OK_123456",0

buffer times 32 db 0

key db 0
salt times 8 db 0
verifier_enc times 16 db 0
verifier_buf times 16 db 0

buffer_disk times 512 db 0
salsa_state times 64 db 0
salsa_buf times 64 db 0

dap:
    db 16,0
    dw 0
    dd 0
    dw 0
    dq 0