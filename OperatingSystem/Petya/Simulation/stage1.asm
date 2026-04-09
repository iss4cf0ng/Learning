; stage1.asm
BITS 16
ORG 0x7C00

start:
    mov ax, 0
    mov es, ax
    mov bx, 0x8000

    mov ah, 0x02
    mov al, 4          ; read 4 byte
    mov ch, 0
    mov cl, 2
    mov dh, 0
    mov dl, 0x80
    int 0x13

    jmp 0x0000:0x8000

times 510 - ($ - $$) db 0
dw 0xAA55