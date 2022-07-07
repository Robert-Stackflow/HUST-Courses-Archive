.686P
.model flat, c
  ExitProcess PROTO STDCALL :DWORD
  includelib  kernel32.lib
  includelib  libcmt.lib
  includelib  legacy_stdio_definitions.lib
  printf          PROTO C :ptr sbyte, :VARARG
  scanf          PROTO C :ptr sbyte, :VARARG
.DATA
  lpFmt	db	"%d",0ah, 0dh, 0
  BUF  DD  -20,50,-30,6,100,-200,70
  N    =  ($-BUF)/4
  R    DD  0
  lp   db '%19s',0
  buf1 db 20 dup(0)

.STACK 200
.CODE
main  proc
   invoke scanf, offset lp, offset buf1
   LEA  EBX, BUF  
   MOV  ECX, N
   XOR  EAX, EAX
LOPA: 
   CMP  DWORD PTR [EBX],0
   JGE  NEXT
   INC  EAX
NEXT:
   ADD  EBX, 4
   DEC  ECX
  
   JNZ  LOPA
   MOV  R, EAX
   invoke printf,offset lpFmt, R
   invoke ExitProcess, 0
main  endp
end