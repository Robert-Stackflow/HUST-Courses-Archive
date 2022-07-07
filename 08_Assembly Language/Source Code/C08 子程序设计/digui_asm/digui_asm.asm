.686P
.model flat, stdcall
  ExitProcess PROTO STDCALL :DWORD
  includelib  kernel32.lib
  printf      PROTO C :ptr sbyte, :VARARG
  includelib  libcmt.lib   
  includelib  legacy_stdio_definitions.lib

.DATA
  lpFmt	   DB	"%d", 0dh,0ah,0
.STACK 200
.CODE
JIECHENG  PROC 
   LOCAL T: DWORD
   CMP   DWORD PTR [EBP+8], 1
   JNE   LP
   MOV   EAX, 1
   RET   4
LP:
   MOV   EAX, [EBP+8] 
   DEC   EAX
   PUSH  EAX
   CALL  JIECHENG

   MOV  T, EAX
   IMUL  EAX, [EBP+8]
   RET   4
JIECHENG ENDP

main proc c
   PUSH   3
   CALL   JIECHENG
   invoke printf,offset lpFmt, EAX
   invoke ExitProcess, 0
main endp
END