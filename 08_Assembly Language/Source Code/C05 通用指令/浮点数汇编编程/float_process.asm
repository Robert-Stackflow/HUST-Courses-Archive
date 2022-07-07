.486
.model flat, stdcall
  ExitProcess PROTO STDCALL :DWORD
  includelib  kernel32.lib
  includelib      msvcrt.lib
  printf          PROTO C :ptr sbyte, :VARARG
 
.DATA
  lpFmt	db	"%f",0ah, 0dh, 0
  X  REAL4  3.14
  Y  REAL4  5.701
  Z  REAL4  0.0
.STACK 200
.CODE
 START: 
   FINIT
   FLD  X
   FADD  Y
   FST  Z
   MOV  EAX, Z
   PUSH EAX
   invoke printf,offset lpFmt
   invoke ExitProcess, 0
END START 