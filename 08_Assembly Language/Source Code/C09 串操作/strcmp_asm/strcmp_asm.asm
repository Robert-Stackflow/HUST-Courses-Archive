.686P
.model flat, c
  ExitProcess PROTO STDCALL :DWORD
  includelib  libcmt.lib   
  includelib  legacy_stdio_definitions.lib
  printf          PROTO  :ptr sbyte, :VARARG
  getchar         PROTO 
.DATA
  MSG1        DB   'NOT '
  MSG2        DB   'EQUAL', 0dh,0ah,0
  buf1        DB   'AB', 9998 DUP(0)
  buf2        DB   'CD', 9998 DUP (0)
.STACK 200
.CODE
CMP_OPT PROC
   MOV  ECX, [EDX]
   MOV  EBX,'aaaa'
   XOR  ECX, EBX
   MOV  EDI, 7EFEFEFFH
   ADD  EDI, ECX
   XOR  ECX,0FFFFFFFFH
   XOR  ECX, EDI
   AND  ECX, 81010100H
   RET
CMP_OPT ENDP

main  proc
   LEA    ESI, BUF1
   LEA    EDI, BUF2
   MOV    ECX, 10000
   CLD
   REPZ   CMPSB
   JZ     DISPLAY_EQU
   invoke printf,offset MSG1 
   JMP    EXIT 
DISPLAY_EQU:
    invoke printf,offset MSG2  
EXIT:
   invoke getchar
   invoke Exitprocess, 0
main  endp
end