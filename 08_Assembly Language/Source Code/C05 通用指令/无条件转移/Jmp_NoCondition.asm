.386
.model flat, stdcall
  ExitProcess PROTO STDCALL :DWORD
  includelib  kernel32.lib
  includelib      msvcrt.lib
  printf          PROTO C :ptr sbyte, :VARARG
 
.DATA
  lpFmt	db	"%d",0ah, 0dh, 0
  X  DD  1234H
  P  DD  L1
.STACK 200
.CODE
 START: 

   JMP   L1
   MOV   EBX, P
   JMP   EBX
   JMP   P
   MOV   EBX, OFFSET P
   JMP   DWORD PTR [EBX]
 L1:
   invoke printf,offset lpFmt,eax
   invoke ExitProcess, 0
END START 