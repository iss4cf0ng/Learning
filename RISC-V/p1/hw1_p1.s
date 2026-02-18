.globl __start

.rodata
    msge: .string "\n "
    msg0: .string "This is HW1-1: Extended Euclidean Algorithm\n"
    msg1: .string "Enter a number for input x: "
    msg2: .string "Enter a number for input y: "
    msg3: .string "The result is:\n "
    msg4: .string "GCD: "
    msg5: .string "a: "
    msg6: .string "b: "
    msg7: .string "inv(x modulo y): "

.text
################################################################################
  # You may write function here
euclidean:
    addi sp, sp, -20 #
    sw x0, 16(sp) # a
    sw x0, 12(sp) # b
    sw a0, 8(sp) # x
    sw a1, 4(sp) # y
    sw x1, 0(sp)
    
    bgt a1, x0, L1
    addi sp, sp, 20
    
    add s0, x0, a0 # GCD
    addi s5, x0, 1
    sw s5, 16(sp) # a
    addi s5, x0, 0
    sw s5, 12(sp) # b
    
    jalr x0, 0(x1)
    
  L1:
    div s4, a0, a1 # q
    mul s5, s4, a1 # temp = q * y
    sub s6, a0, s5 # r = x - q * y
    add a0, x0, a1 # new x
    add a1, x0, s6 # new y
    jal x1, euclidean
    
    lw s5, 16(sp) # a
    lw s6, 12(sp) # b
    lw a0, 8(sp) # x
    lw a1, 4(sp) # y
    lw x1, 0(sp) # ret addr
    
    div s4, a0, a1 # q
    add s1, x0, s6 # a = b
    mul s7, s4, s1 # temp = q * b
    sub s7, s5, s7 # temp = a - q * b
    add s2, x0, s7 # b = a - q * b

    addi sp, sp, 20
    beq sp, s8, End
    sw s1, 16(sp) # a
    sw s2, 12(sp) # b
    
    End:
    
    jalr x0, 0(x1)
    
div_negative:
  
  jalr x0, 0(x1)
    
mod_inv:
  # START FROM HERE
  # FOR ax + by = gcd(x, y)
  # s0: GCD, s1: a and s2: b
  addi s5, x0, 1
  beq s0, s5, L # IF s0(GCD) == 1 GO TO 'L'
  add s3, x0, x0
  beq x0, x0, E # ALWASY TRUE. IT WILL NOT RUN THE CODE OF AREA 'L'
  L:
    # inv(x mod y) -> a % y = r = a - (a // y) * y
    #div s4, s1, a1 # q = a // y
    
  blt s1, x0, N
  div s4, s1, a1
  beq x0, x0, E1
  N:
  add s5, x0, a1
  sub s5, s5, s1
  addi s6, x0, 1
  sub s5, s5, s6
  div s4, s5, a1
  addi s6, x0, -1
  mul s4, s4, s6
  E1:
  
  mul s5, s4, a1 # q * y
  sub s3, s1, s5 # a - q * y
  E:
  
  jalr x0, 0(x1)
    
################################################################################
__start:
  # Prints msg0
    addi a0, x0, 4
    la a1, msg0
    ecall

  # Prints msg1
    addi a0, x0, 4
    la a1, msg1
    ecall

  # Reads int1
    addi a0, x0, 5
    ecall
    add t0, x0, a0
    
  # Prints msg2
    addi a0, x0, 4
    la a1, msg2
    ecall
    
  # Reads int2
    addi a0, x0, 5
    ecall
    add a1, x0, a0
    add a0, x0, t0
    addi t0, x0, 0
    
################################################################################ 
  # You can do your main function here
main:
  la x1, result
  add s8, x0, sp
  add s1, x0, x0
  add s2, x0, x0
  
  jal x1, euclidean
  # FOR ax + by = gcd(x, y)
  # AFTER WE EXECUTED THE ABOVE INSTRUCTION,
  # THEN s0 STORES GCD, s1 STORES a and s2 STORES b
  
  jal x1, mod_inv
    
################################################################################

result:
    addi t0,a0,0
  # Prints msg
    addi a0, x0, 4
    la a1, msg3
    ecall
    
    addi a0, x0, 4
    la a1, msg4
    ecall

  # Prints the result in s0
    addi a0, x0, 1
    add a1, x0, s0
    ecall
    
    addi a0, x0, 4
    la a1, msge
    ecall
    addi a0, x0, 4
    la a1, msg5
    ecall
    
  # Prints the result in s1
    addi a0, x0, 1
    add a1, x0, s1
    ecall
    
    addi a0, x0, 4
    la a1, msge
    ecall
    addi a0, x0, 4
    la a1, msg6
    ecall
    
  # Prints the result in s2
    addi a0, x0, 1
    add a1, x0, s2
    ecall
    
    addi a0, x0, 4
    la a1, msge
    ecall
    addi a0, x0, 4
    la a1, msg7
    ecall
    
  # Prints the result in s3
    addi a0, x0, 1
    add a1, x0, s3
    ecall
    
  # Ends the program with status code 0
    addi a0, x0, 10
    ecall    