.686P
.model flat, stdcall
  ExitProcess PROTO STDCALL :DWORD
  includelib  kernel32.lib
 ; includelib      msvcrt.lib
 includelib   libcmt.lib
 includelib   legacy_stdio_definitions.lib
  printf          PROTO C :ptr sbyte, :VARARG
;  myfadd            PROTO C :DWORD, :DWORD
.DATA
  lpFmt	   DB	"%d ", 0dh,0ah,0
.STACK 200
.CODE
 myfadd  PROC C X:DWORD, Y:DWORD
       LOCAL U:DWORD,V:DWORD,W:DWORD
	   MOV   EAX, X[ESI]
	   ADD   EAX, 10
	   MOV   U,   EAX    ; U=X+10;
	   MOV   EAX, Y
	   ADD   EAX, 25
	   MOV   V,   EAX    ; V=Y+25;
	   ADD   EAX, U
	   MOV   W,   EAX    ; W=U+V;
	   RET
myfadd   ENDP

main PROC c
     LOCAL  A:DWORD
	 LOCAL  B:DWORD,SUM:DWORD
     MOV   A, 100
	 MOV   B, 200
     INVOKE MYFADD, A, B
	 MOV   SUM, EAX
     invoke printf,offset lpFmt, SUM
     invoke ExitProcess, 0
	 RET
main  ENDP
END