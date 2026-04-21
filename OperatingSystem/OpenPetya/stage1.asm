; stage1.asm

BITS 16
ORG 0x7C00

start:
    cli

    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00

    sti

    ; load stage2 to 0x8000
    mov bx, 0x8000
    mov ah, 0x02
    mov al, 4          ; 4 sectors
    mov ch, 0
    mov cl, 2          ; sector 2
    mov dh, 0
    mov dl, 0x80

    int 0x13
    jc disk_error      ; VERY IMPORTANT

    jmp 0x0000:0x8000

disk_error:
    mov si, err_msg
.print:
    lodsb
    cmp al, 0
    je $
    mov ah, 0x0E
    int 0x10
    jmp .print

err_msg db "Disk read error!",0

times 510 - ($ - $$) db 0
dw 0xAA55