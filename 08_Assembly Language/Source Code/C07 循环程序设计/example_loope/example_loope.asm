.686P
.model flat, stdcall
  ExitProcess PROTO STDCALL :DWORD
  includelib  kernel32.lib
  includelib      libcmt.lib
  includelib    legacy_stdio_definitions.lib
  printf          PROTO C :ptr sbyte, :VARARG
.DATA
  lpFmt	db	"%d",0ah, 0dh, 0
  BUF  db  10,6 dup(0), 20, 10 dup(0)
  N    =  ($-BUF)
  X    DD  0
.STACK 200
.CODE
main proc c
   MOV  ECX, N
   MOV  EBX, -1
LOPA:
   INC  EBX
   CMP  BUF[EBX],0
   LOOPE LOPA
   JZ   ALL_ZERO
   MOV  X, 1
   JMP  EXIT
ALL_ZERO:
   MOV  X, 0
EXIT:
   invoke printf,offset lpFmt, X
   invoke ExitProcess, 0
main endp
end