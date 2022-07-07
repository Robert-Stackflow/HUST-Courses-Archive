.686P
.MMX
.model flat, c
  ExitProcess PROTO STDCALL :DWORD
  includelib  libcmt.lib   
  includelib  legacy_stdio_definitions.lib
  printf          PROTO  :ptr sbyte, :VARARG
  clock           PROTO 
  getchar         PROTO 
  
.DATA
  BUF1        DB   1000001 DUP(0)
  BUF2        DB   10000 DUP (1)
  begin_time  DD   0
  end_time    DD   0
  spend_time  DD   0         ; 运行时间(豪秒)
    lpFmt	      DB	"%d", 0dh,0ah,0

.STACK 200
.CODE
main proc c
   invoke clock
   MOV    BEGIN_TIME, EAX
   INC    EAX

   LEA  EAX, BUF1
   MOV  ECX, 1000000/8
 L_SCA:
   MOVQ MM0, QWORD PTR[EAX]
   ADD  EAX,8
   DEC  ECX
   JNZ  L_SCA
   
   invoke clock
   MOV    END_TIME, EAX
   SUB    EAX, BEGIN_TIME
   MOV    SPEND_TIME, EAX
   invoke printf,offset lpFmt, EAX
   invoke getchar
   invoke Exitprocess, 0
main endp
end
 