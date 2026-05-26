; shellcode.asm
BITS 32
    xor eax, eax    ; zero out eax
    ret             ; return cleanly to caller