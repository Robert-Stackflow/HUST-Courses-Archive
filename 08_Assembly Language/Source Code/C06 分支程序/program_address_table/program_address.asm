.686P
.model flat, stdcall
  ExitProcess PROTO STDCALL :DWORD
  includelib  kernel32.lib
  ; includelib      msvcrt.lib
 ; printf          PROTO C :ptr sbyte, :VARARG
  ;includelib  libcmt.lib
 ; includelib  legacy_stdio_definitions.lib  
 ; public L1,L2,L3
.DATA
  lpFmt	db	"%s",0ah, 0dh, 0
  X     DD  3
  MSG1  DB  'Hello,One',0
  MSG2  DB  'Two',0
  MSG3  DB  'Welcome,Three',0
  PTABLE  DD  L1,L2,L3


.STACK 200
.CODE
start:
;main proc c
   MOV  EBX, X  
   MOV  EAX, PTABLE[EBX*4 -4]
   JMP  EAX
L1:
 ;  invoke printf,offset lpFmt, OFFSET MSG1
   JMP    EXIT
L2:
 ;  invoke printf,offset lpFmt, OFFSET MSG2
   JMP    EXIT
 L3:
 ;  invoke printf,offset lpFmt, OFFSET MSG3
EXIT:
   invoke ExitProcess, 0
;main endp

;END
end start