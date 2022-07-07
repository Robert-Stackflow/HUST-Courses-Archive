.686P
.model flat, stdcall
  ExitProcess PROTO STDCALL :DWORD
  includelib  kernel32.lib
  includelib  libcmt.lib
 includelib  legacy_stdio_definitions.lib
  printf          PROTO C :ptr sbyte, :VARARG
.DATA
  lpFmt	   DB	"%d", 0dh,0ah,0

.STACK 200
.CODE
JIECHENG  PROC  c X:DWORD
   LOCAL T: DWORD
   CMP   X, 1
   JNE   LP
   MOV   EAX, 1
   RET   
LP:
   MOV   EAX, X
   DEC   EAX
   INVOKE  JIECHENG,EAX
   MOV  T, EAX
   IMUL  EAX, X
   RET   
JIECHENG ENDP
main proc  c
   INVOKE   jiecheng, 4
   invoke printf,offset LPFMT, EAX
   invoke ExitProcess, 0
   main endp
END