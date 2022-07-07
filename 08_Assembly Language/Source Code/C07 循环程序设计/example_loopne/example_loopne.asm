.686P
.model flat, stdcall
  ExitProcess PROTO STDCALL :DWORD
  includelib  kernel32.lib
  includelib      msvcrt.lib
  printf          PROTO C :ptr sbyte, :VARARG
  includelib      libcmt.lib
  includelib    legacy_stdio_definitions.lib

.DATA
  lpFmt	DB	"%d",0ah, 0dh, 0
  BUF  DB  'This is a test'
  N    =  ($-BUF)
  X    DD  0
.STACK 200
.CODE
main  proc  c
   MOV  ECX, N
   MOV  EBX, -1
LOPA:
   INC  EBX
   CMP  BUF[EBX],' '
   LOOPNE LOPA
   JZ   SPACE_OCCUR
   MOV  X, -1
   JMP  EXIT
SPACE_OCCUR:
   MOV  X, EBX
EXIT:
   invoke printf,offset lpFmt, X
   invoke ExitProcess, 0
main endp
END