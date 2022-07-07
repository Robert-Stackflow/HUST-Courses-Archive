.686P     
.model flat, stdcall
 ExitProcess PROTO STDCALL :DWORD
 includelib  kernel32.lib  ; ExitProcess 在 kernel32.lib中实现
 printf          PROTO C :VARARG
 includelib  libcmt.lib
 includelib  legacy_stdio_definitions.lib

.DATA
 X   DB 1,2,3,4
 Y   DW 20H
 Z   DW 30H
 lpFmt	db	"%c",0ah, 0dh, 0
.STACK 200
.CODE
main proc c

   MOV  X+1,32H
   MOV  X[1],32H
   MOV  [X+1],32H
   MOV  AH,X+2

   invoke printf,offset lpFmt,AL
   invoke ExitProcess, 0
main endp
END