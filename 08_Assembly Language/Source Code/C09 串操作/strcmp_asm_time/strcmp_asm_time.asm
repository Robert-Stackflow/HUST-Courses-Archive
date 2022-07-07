.686P
.model flat, c
  ExitProcess PROTO STDCALL :DWORD
  includelib  libcmt.lib   
  includelib  legacy_stdio_definitions.lib
  printf          PROTO  :ptr sbyte, :VARARG
  clock           PROTO 
  getchar         PROTO 
  
.DATA
  lpFmt	      DB	"%d", 0dh,0ah,0
  BUF1        DB   1000000 DUP(0)
  BUF2        DB   10000 DUP (1)
  begin_time  DD   0
  end_time    DD   0
  spend_time  DD   0         ; 运行时间(豪秒)
.STACK 200
.CODE
main proc
   invoke clock
   MOV    BEGIN_TIME, EAX

   LEA  EDI, BUF1
   MOV  ECX, 1000000
   MOV  AL,'a'
 L_SCA:
   CMP  [EDI],AL
   JZ   L3
   INC  EDI
   DEC  ECX
   JNZ  L_SCA
   JMP  L3

   LEA  EDI, BUF1
   MOV  AL,'a'
   CLD
   MOV  ECX, 1000000
   REPNE SCASB

   LEA  EDX, BUF1
   MOV  EAX, 1000000/4
L1:
   MOV  ECX, [EDX]

   MOV  EBX,'aaaa'
   XOR  ECX, EBX
   MOV  EDI, 7EFEFEFFH
   ADD  EDI, ECX
   XOR  ECX,0FFFFFFFFH
   XOR  ECX, EDI
   ADD  EDX, 4
   AND  ECX, 81010100H
   JNZ  L2
   DEC  EAX
   JNZ  L1
   JMP  L3

L2:  ; 找到了要找的字符
L3:  ; 未找到相应的字符

   invoke clock
   MOV    END_TIME, EAX
   SUB    EAX, BEGIN_TIME
   MOV    SPEND_TIME, EAX
   invoke printf,offset lpFmt, EAX
   invoke getchar
   invoke Exitprocess, 0
main endp
end