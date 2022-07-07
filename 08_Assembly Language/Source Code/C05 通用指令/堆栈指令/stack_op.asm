.386
.model flat, stdcall
  ExitProcess PROTO STDCALL :DWORD
  includelib  kernel32.lib
  includelib      msvcrt.lib
  printf          PROTO C :ptr sbyte, :VARARG
 
.DATA
  lpFmt	db	"%d",0ah, 0dh, 0
  X  DD  1234H
.STACK 200
.CODE
 START: 
   MOV BL, 1
   MOV AX,1234H
   DIV BL
   POP EAX
   MOV EBX,[ESP-4]

   LDS  BX, X
   PUSH EAX
   PUSH X
   invoke printf,offset lpFmt,eax
   invoke ExitProcess, 0
END START 