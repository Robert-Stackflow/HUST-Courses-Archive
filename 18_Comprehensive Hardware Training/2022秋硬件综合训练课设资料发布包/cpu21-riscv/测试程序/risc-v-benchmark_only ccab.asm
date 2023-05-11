.text

#j benchmark_start       #delete this instruction for ccmb bencmark
#C1 instruction benchmark

nop
auipc s1,0x430
add a0,zero,s1
addi a7,zero,34         # system call for print
ecall                  # print
auipc s1,0x430
add a0,zero,s1
addi a7,zero,34         # system call for print
ecall                  # print
auipc s1,0x430
add a0,zero,s1
addi a7,zero,34         # system call for print
ecall                  # print
auipc s1,0x430
add a0,zero,s1
addi a7,zero,34         # system call for print
ecall                  # print
auipc s1,0x430
add a0,zero,s1
addi a7,zero,34         # system call for print
ecall                  # print
auipc s1,0x430
add a0,zero,s1
addi a7,zero,34         # system call for print
ecall                  # print
auipc s1,0x430
add a0,zero,s1
addi a7,zero,34         # system call for print
ecall                  # print
auipc s1,0x430
add a0,zero,s1
addi a7,zero,34         # system call for print
ecall                  # print
addi   a7,zero,10         # system call for exit
ecall                  # we are out of here.

#C2 instruction benchmark

addi t0,zero,-1
addi t1,zero,0

addi s0,zero,0x19
slli s0,s0,8
addi s1,zero,0x97


sltiu_branch:
add a0,s0,s1
addi a7,zero,34        # system call for print
ecall                  # print
add s1,s1,t0
sltiu t1,s1, 0x49
beq t1,zero,sltiu_branch

addi   a7,zero,10         # system call for exit
ecall                  # we are out of here.

#Mem instruction benchmark


addi t1,zero,0     #init_addr
addi t3,zero,16     #counter

#???д?????????????????????? 0x81,82,84,86,87,88,89.......???????

addi s1,zero,  0x84
slli s1,s1,8
addi s1,s1,0x83
addi s2,zero,  0x04
slli s2,s2,8
addi s2,s2,0x04
slli s1,s1,8
addi s1,s1,0x82
slli s1,s1,8
addi s1,s1,0x81
slli s2,s2,8
addi s2,s2,0x04
slli s2,s2,8
addi s2,s2,0x04    #    init_data= 0x84838281 next_data=init_data+ 0x04040404

lhu_store:
sw s1,(t1)
add s1,s1,s2   #data +1
addi t1,t1,4    # addr +4
addi t3,t3,-1   #counter
bne t3,zero,lhu_store

addi t3,zero,32   #???????
addi t1,zero,0    # addr
lhu_branch:
lhu s1,(t1)     #???????
add a0,zero,s1
addi a7,zero,34
ecall                  # print
addi t1,t1, 2
addi t3,t3, -1
bne t3,zero,lhu_branch

addi   a7,zero,10         # system call for exit
ecall                  # we are out of here.


#Branch instruction benchmark

addi s1,zero,15  #初始值
bge_branch:
add a0,zero,s1
addi a7,zero,34
ecall                  # 输出当前值
addi s1,s1,-1
bge s1,zero,bge_branch   #测试指令

addi   a7,zero,10         #停机指令
ecall                  # 系统调用

 addi   a7,zero,10         # system call for exit
 ecall                  # we are out of here.

 #处理器实现中请用停机指令实现ecall
