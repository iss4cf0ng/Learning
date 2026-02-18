.globl __start

__start:
lui s0,16
addi s0,s0,0x64

addi a0,x0,1
addi a1,x0,5
addi a2,x0,64
addi a3,x0,-4
addi a4,x0,1000

#lw a0,0(s0)
#lw a1,4(s0)
#lw a2,8(s0)
#lw a3,12(s0)
#lw a4,16(s0)

add t1,a0,a1
sub t2,a0,a1
mul t0,t1,t2
srli t1,a2,2
srai t2,a3,1
mul t3,t1,t2
add t0,t0,t3

slti t1,x0,1
slti t2,x0,-1
sub t3,t1,t2
slli t3,t3,2
mul t0,t0,t3
remu t1,a4,a2
divu t2,t1,a1
sub t0,t0,t2

sw t0,20(s0)
