.globl __start

mod:
  div t0, a1 , a0
  mul t1, a0 , t0  
  sub t0, a1 , t1
  jalr x0,0(x1)
    
__start: #x:a0,y:a1
    lui s4,16
    addi s4,s4,0xFC
  
    #lw a0,0(s4)
    #lw a1,4(s4)
    addi a0,x0,114
    addi a1,x0,514
    
    addi s11,x0,0 #record iter num
    addi s10,x0,1 #data number
    jal x1,down

down:
    beq a0,x0,up_init
    addi sp,sp,-8
    sw a1,4(sp)
    sw a0,0(sp)
    jal x1,mod #get mod to t0
    add a1,x0,a0
    add a0,x0,t0
    addi s11,s11,1
    jal x1,down
   
up_init:
    addi s1,x0,0 #x
    addi s2,x0,1 #y
    add s0,x0,a1 #store gcd
    lw a1,4(sp)
    lw a0,0(sp)
    addi sp,sp,8
    addi s11,s11,-1
    
up:
    div t0,a1,a0
    mul t0,t0,s1
    sub t0,s2,t0
    add s2,x0,s1
    add s1,x0,t0
    add s3,x0,s1 # store x into s3
    beq s11,x0,mod_inv
    lw a1,4(sp)
    lw a0,0(sp)
    addi sp,sp,8
    addi s11,s11,-1
    jal x1,up
    
mod_inv:
    addi t0,x0,1
    bne s0,t0,mod_nan
    blt s3,x0,add_x
    bge s3,a1,sub_x
    jal x1,result
    
mod_nan:
    addi s3,x0,0
    jal x1,result
    
add_x:
    add s3,s3,a1
    jal x1,mod_inv
    
sub_x:
    sub s3,s3,a1
    jal x1,mod_inv
    
################################################################################

result: # store s0~s3
    sw s0,8(s4)
    sw s1,12(s4)
    sw s2,16(s4)
    sw s3,20(s4)
    addi s10,s10,-1
    blt s10,x0,end
    addi s4,s4,24
    addi s11,x0,0 #record iter num
    #lw a0,0(s4)
    #lw a1,4(s4)
    addi a0,x0,1919
    addi a1,x0,810
    jal x1,down
    
end:
    
