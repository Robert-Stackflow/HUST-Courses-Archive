.686P
.model flat, stdcall
  ExitProcess PROTO STDCALL :DWORD
  includelib  kernel32.lib
  includelib  libcmt.lib
 includelib  legacy_stdio_definitions.lib
  printf          PROTO C :ptr sbyte, :VARARG
.DATA
  lpFmt	db	"%s",0ah, 0dh, 0
  X     DD  3
  MSG1  DB  'Hello,One',0
  MSG2  DB  'Two',0
  MSG3  DB  'Welcome,Three',0
  VTABLE  DD  MSG1, MSG2, MSG3

.STACK 200
.CODE
 main  proc  c 
   MOV  EBX, X  
   MOV  EAX, VTABLE[EBX*4 -4]
   invoke printf,offset lpFmt, EAX
   invoke ExitProcess, 0
main  endp
end