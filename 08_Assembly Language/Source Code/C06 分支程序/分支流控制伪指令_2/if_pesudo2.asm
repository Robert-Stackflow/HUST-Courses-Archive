.686P
.model flat, stdcall
  ExitProcess proto STDCALL :DWORD
  includelib  kernel32.lib
  printf      proto C :ptr sbyte, :VARARG
  includelib  libcmt.lib
  includelib  legacy_stdio_definitions.lib  

.DATA
  lpFmt	db	"x=%d y=%d r=%d",0ah, 0dh, 0
  x  sdword  -5
; x  dword  -5
  y  sdword  6
; y  dword  6
  r  sdword  0
  count  DD 26 dup(0)
  buf  db 'abcdabb',0
.STACK 200
.CODE
main proc c
   mov r, 0
   .if x>=0 && y>=0
	      mov  r, 1
   .endif
   .if x<0 && y<0
	    mov  r, -1
   .endif
   invoke printf,offset lpFmt,x,y,r

   MOV  EBX,  0
L1:
   MOV  AL, BUF[EBX]
   CMP  AL, 0
   JE   EXIT
   SUB  AL, 'a'
   MOVZX  EAX, AL
   INC    COUNT[EAX*4]
   INC    EBX
   JMP    L1

   exit:
   invoke ExitProcess, 0
main endp
END