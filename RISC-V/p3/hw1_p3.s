.globl __start

.rodata
    O_RDWR: .word 0b0000100
    msg1: .string "This is problem 3\n"
    msg2: .string " "
.text

__start:
  li a0, 4
  la a1, msg1
  ecall
  li a0, 13      # ecall code
  la a1, pattern
  lw a2, O_RDWR  # load O_RDWR open flag
  ecall
  # Load address of the input string into a0
  add a1, x0, a0
  li a0, 14      # ecall code
  li a2, 0x10200 # modify to a bigger number if your code is too long
  li a3, 94      # number of bytes to read
  ecall
  li a0, 16
  ecall
  addi t0, x0, 94
  add t1, x0, x0
Shift_ascii:
  add t3, t1, a2
  lb t2, 0(t3)
  addi t2, t2, -32
  add t3, t1, a2
  sb t2, 0(t3)
  addi t1, t1, 1
  bne t0, t1, Shift_ascii
  jal x0, your_function

Exit:
  li a0, 1
  add a1, x0, t0
  ecall
  beq t0, x0, Terminate
  li a0, 4
  la a1, msg2
  ecall
  li a0, 1
  add a1, x0, t1
  ecall
Terminate:
  addi a0, x0, 10
  ecall
################################################################################
# DO NOT MODIFY THE CODE ABOVE
################################################################################

.rodata
    # pattern: .string "../../b10901119_hw1/p3/pattern0.txt"
    # pattern: .string "../../b10901119_hw1/p3/pattern1.txt"
    # pattern: .string "../../b10901119_hw1/p3/pattern2.txt"
.text

# Write your main function here.
# a2(i.e.,x12) stores the heads address
# store whether there is cycle in t0
# store the entry point in t1
# go to Exit when your function is finish

your_function:
  addi a0, x0, 94 # NULL
  
  li a3, 0x11000 # STORE THE NODES THAT HAVE BEEN SEEN
  sb a0, 0(a3)
  
  j main # GO TO MAIN FUNCTION
  F:
  # IN THIS FUNCTION, a4 IS OUR COMPARISON SAMPLE
  # THE RESULT OF FUNCTION 'F' WILL BE STORED IN REGISTER 't2'
  add t2, x0, x0 # INIT t2 = 0 (result)
  li t4, 0x11000
  FL:
  lb t3, 0(t4)
  beq t3, a0, EndFL # while (t3 < 94)
  # HERE IS t3 != 94
  addi t4, t4, 1
  bne t3, a4, FL
  # HERE IS t3 == a4 (INTEGER FOUND)
  addi t2, x0, 1 #t2 (RESULT) = 1
  j EndFL # BREAK (END LOOP)
  
  addi a3, a3, 1 # NEXT INTEGER (POINTER)
  j FL # LOOP
  
  EndFL:
  jalr x0, 0(x1)
  
  main:
  L:
  lb a4, 0(a2) # LOAD INTEGER FROM a2 AND STORE IN a4
  blt a4, x0, EndL # NULL MEMORY -> NEGATIVE
  jal x1, F # RESULT IN REGISTER 't2'
  
  beq t2, x0, EndmainIf # If (t2 == 0(false)) GOTO 'EndmainIf'
  # HERE IS t2 == 1 (TRUE)
  addi t0, x0, 1 # SET TRUE (FOUND)
  add t1, x0, a4 # SET VALUE OF THE NODE THAT WE FOUND
  j EndL
  
  EndmainIf:
  
  sb a4, 0(a3) # SET CURRENT POINTER: a4(CHAR)
  addi a2, a2, 1 # iAddr += 4
  addi a3, a3, 1 # nAddr += 4
  sb a0, 0(a3) # SET LAST ONE: 94
  j L
  EndL:
  
  bne t0, a0, End
  add t0, x0, x0
  End:
  
  jal x0, Exit