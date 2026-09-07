; file: sub3.asm

%include "asm_io.inc"

segment .data
sum dd 0

segment .bss
input resd 1

; pseudo-code algorithm
; i = 1;
; sum = 0;
; while (get_int(i, &input), input != 0) {
;   sum += input;
;   i++;
; }
; print_sum(num);

segment .text
    global asm_main
asm_main:
    enter 0, 0 ; setup routine
    pusha

    mov edx, 1 ; edx is 'i' in pseudo-code
while_loop:
    push edx ; save i in stack
    push dword input
    call get_int
    add esp, 8 ; remove i and &input from stack (destroyed by caller)

    mov eax, [input]
    cmp eax, 0
    je end_while

    add [sum], eax

    inc edx ; i++
    jmp short while_loop

end_while:
    push dword [sum]
    call print_sum
    pop ecx

    popa
    mov eax, 0
    leave
    ret

; subprogram get_int
; Parameters (in order pushed on stack)
;   number of input (at [ebp+12])
;   address of word to store input into (at [ebp + 8])
; Notes:
;   values of eax and ebx are destroyed
segment .data
prompt db ") Enter an integer number (0 to quit): ", 0

segment .text
get_int:
    push ebp
    mov ebp, esp ; store ESP value into EBP

    mov eax, [ebp + 12]
    call print_int

    mov eax, prompt
    call print_string

    call read_int
    mov ebx, [ebp + 8]
    mov [ebx], eax ; store input into memory

    pop ebp
    ret

segment .data
result db "The sum is ", 0

segment .text
print_sum:
    push ebp
    mov ebp, esp

    mov eax, result
    call print_string

    mov eax, [ebp+8]
    call print_int
    call print_nl

    pop ebp
    ret