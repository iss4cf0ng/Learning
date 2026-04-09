; hello_mbr.asm
BITS 16
ORG 0x7C00

start:
    mov si, message

print:
    lodsb ; AL = [SI]
    cmp al, 0
    je done

    mov ah, 0x0E ; teletype output
    mov bh, 0x00
    mov bl, 0x07 ; white text
    int 0x10

    jmp print

done:
    cli
    hlt

message db "Hello from MBR!", 0
; padding until 510 bytes
times 510 - ($ - $$) db 0

; boot signature
dw 0xAA55