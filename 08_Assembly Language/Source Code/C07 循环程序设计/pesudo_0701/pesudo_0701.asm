.386
.model flat, c
  ExitProcess PROTO STDCALL :DWORD
;  includelib  kernel32.lib
;  includelib      msvcrt.lib
  printf          PROTO  :VARARG
  includelib   libcmt.lib
  includelib   legacy_stdio_definitions.lib
.DATA
  lpFmt	db	"%d",0ah, 0dh, 0
  BUF  SDWORD  -20,50,-30,6,100,-200,70
  N    =  ($-BUF)/4
  R    DD  0
.STACK 200
.CODE
main  proc
   XOR  EAX, EAX
   XOR  EBX, EBX  
   MOV  ECX,N
 .REPEAT
   .IF BUF[EBX*4]<0
       INC  EAX
   .ENDIF
   INC  EBX
;   .until  ecx==5
.UNTILCXZ  ebx==5
   MOV  R, EAX
   invoke printf,offset lpFmt, R
   invoke ExitProcess, 0
   main  endp
END