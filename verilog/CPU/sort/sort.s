.globl __start

swap:
slli x6,x11,2# reg x6 = k * 4
add x6,x10,x6 # reg x6 = v + (k * 4)
lw x5,0(x6)# reg x5 (temp) = v[k]
lw x7,4(x6)# reg x7 = v[k + 1]
sw x7,0(x6)# v[k] = reg x7
sw x5,4(x6)# v[k+1] = reg x5 (temp)
jalr x0,0(x1)# return to calling routine

__start:
lui x10,16
addi x10,x10,0x80 #array, (no initial memory: 0xC0, has memory: 0x80)
addi x11,x0,8 #n

# addi x1,x0,5
# sw x1,0(x10)
# addi x1,x0,6
# sw x1,4(x10)
# addi x1,x0,7
# sw x1,8(x10)
# addi x1,x0,8
# sw x1,12(x10)
# addi x1,x0,1
# sw x1,16(x10)
# addi x1,x0,2
# sw x1,20(x10)
# addi x1,x0,3
# sw x1,24(x10)
# addi x1,x0,4
# sw x1,28(x10)

addi x19,x0,1 # i = 1
for1tst:
bge x19,x11,exit1 # go to exit1 if x19 ≥ x11 (i≥n)
addi x20,x19,-1 # j = i −1
for2tst:
blt x20,x0,exit2 # go to exit2 if x20 < 0 (j < 0)
slli x5,x20,2 # reg x5 = j * 4
add x5,x10,x5 # reg x5 = v + (j * 4)
lw x6,0(x5) # reg x6 = v[j]
lw x7,4(x5) # reg x7 = v[j + 1]
bge x7,x6,exit2 # go to exit2 if x6 ≤ x7

addi sp,sp,-4
sw x11,0(sp)
addi x10, x10, 0 # first swap parameter is v
addi x11, x20, 0 # second swap parameter is j
jal x1,swap # call swap
lw x11,0(sp)
addi sp,sp,4

addi x20,x20,-1 # j –= 1
jal x0,for2tst # branch to test of inner loop
exit2:
addi x19,x19,1 # i += 1
jal x0,for1tst 
exit1: