.globl __start

.rodata
    msg0: .string "This is HW1-2: Longest Substring without Repeating Characters\n"
    msg1: .string "Enter a string: "
    msg2: .string "Answer: "
.text

# Please use "result" to print out your final answer
################################################################################
# result function
# Usage: 
#     1. Store the beginning address in t4
#     2. Use "j print_char"
#     The function will print the string stored t4
#     When finish, the whole program will return value 0
result:
    addi a0, x0, 4
    la a1, msg2
    ecall
    
    add a1, x0, t4
    ecall
# Ends the program with status code 0
    addi a0, x0, 10
    ecall
################################################################################

__start:
# Prints msg
    addi a0, x0, 4
    la a1, msg0
    ecall
    
    la a1, msg1
    ecall
    
    addi a0, x0, 8
    
    li a1, 0x10200
    addi a2, x0, 2047
    ecall
# Load address of the input string into a0
    add a0, x0, a1

################################################################################
# DO NOT MODIFY THE CODE ABOVE
################################################################################  
# Write your main function here. 
# a0 stores the beginning address (66048(0x10200)) of the  Plaintext

__main:
  addi t1, x0, '\n' # END OF STRING (LAST CHAR)
  li t4, 0x12000
  sb t1, 0(t4)
  
  addi a1, x0, 0 # LEFT
  addi a2, x0, 0 # RIGHT
  addi a3, x0, 0 # CURRENT LENGTH
  addi a4, x0, 0 # MAXIMUM LENGTH
  addi a6, x0, 0 # idx_start
  
  j main # DO NOT RUN THE FUNCTION CODE
  # ---------- FUNCTION 'F' ----------
  F:
  # THE PARAMETER (CHAR) IS STORED IN a5
  # THE RESULT STORE IN t2
  
  li t5, 0x12000
  add t2, x0, x0 # RESULT = 0 (FALSE)
  FL: # LOOP INSIDE 'F'
  lb t6, 0(t5) # LOAD CHAR
  beq t6, t1, EndFL # while (t6 != '\n')
  addi t5, t5, 1 # NEXT ELEMENT
  bne t6, a5, FL # If (t6 != a5(char)) GOTO FL
  # If (t6 == a5(char))
  add t2, x0, t1 # RESULT = '\n' (WHICH IS IMPOSSIBLE BECAUSE beq)
  EndFL:
  
  jalr x0, 0(x1)
  # ---------- END OF FUNCTION 'F' ----------

  main:
  
  L:
  lb a5, 0(a0) # LOAD CHAR FROM a0
  beq a5, t1, EndL # while (a5 != '\n')
  jal x1, F # FUNCTION
  
  bne t2, t1, Else1 # If t2(char) != '\n' (Not found) GOTO Else1
  # HERE WE FOUND IT
  # CHAR IN 0x12000
  add a1, x0, a2 # LEFT = RIGHT
  li t4, 0x12000 #
  sb t1, 0(t4)
  Else1:
  sb a5, 0(t4) # STORE CHAR INTO t4
  addi t4, t4, 1 # OFFSET
  sb t1, 0(t4) # '\n'
  EndIf1:
  
  sub a3, a2, a1 # right - left
  addi a3, a3, 1 # current_length = right - left + 1
  
  ble a3, a4, EndIf2
  # if (current_length > max_length)
  add a4, x0, a3 # max_length = current_length
  sub a6, a2, a4 #idx_start = right - max_length
  addi a6, a6, 1 # idx_start = right - max_length + 1
  EndIf2:
  
  addi a2, a2, 1 # right++
  
  addi a0, a0, 1 # NEXT CHAR (iAddr++)
  
  j L
  
  EndL:

  add t3, x0, x0 # INDEX OF LOOP L1
  li t4, 0x12000
  li a0, 0x10200
  add a0, a0, a6 # iAddr = _iAddr + idx_start
  L1:
  bge t3, a4, EndL1
  lb t5, 0(a0)
  sb t5, 0(t4) # STORE a0[iAddr] into t4
  
  addi a0, a0, 1 # iAddr++
  addi t4, t4, 1 # oAddr++
  
  addi t3, t3, 1 # i++
  
  sb t1, 0(t4) # STORE '\n'
  
  j L1 # LOOP
  EndL1:
  
  li t4, 0x12000

  j result