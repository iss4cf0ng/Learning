%include "asm_io.inc"
segment .data
Message db "Find primes up to: ", 0

segment .bss
Limit resd 1 ; find primes up to this limit
Guess resd 1 ; the current guess for prime

segment .text
    global asm_main

asm_main:
    enter 0, 0
    pusha

    mov eax, Message
    call print_string
    call read_int ; scanf("%u", &limit);
    mov [Limit], eax
    mov eax, 2 ; printf("2\n");
    call print_int
    call print_nl
    mov eax, 3 ; printf("3\n");
    call print_int
    call print_nl

    mov dword [Guess], 5
while_limit: ; while ( Guess <= Limit )
    mov eax, [Guess]
    cmp eax, [Limit]
    jnbe end_while_limit

    mov ebx, 3
while_factor:
    mov eax, ebx
    mul eax ; eax = eax * eax
    jo end_while_factor
    cmp eax, [Guess]
    jnb end_while_factor
    mov eax, [Guess]
    mov edx, 0
    div ebx ; edx = eax % edx
    cmp edx, 0
    je end_while_factor

    add ebx, 2 ; factor += 2;
    jmp while_factor

end_while_factor:
    je end_if
    mov eax, [Guess]
    call print_int
    call print_nl
end_if:
    add dword [Guess], 2
    jmp while_limit

end_while_limit:

    popa
    mov eax, 0
    leave
    ret