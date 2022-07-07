;.686P
.MMX
.model flat, c
  ExitProcess PROTO STDCALL :DWORD
;  includelib      msvcrt.lib
  printf          PROTO  :VARARG
   includelib  libcmt.lib
 includelib  legacy_stdio_definitions.lib
.DATA
  BUF1        SWORD   1, -2, 3, 400H
  BUF2        SWORD   0,2, 3, 4, 500H,500H
  BUF3        SDWORD   0, 0
  lpFmt	      DB  "%d %x(H)", 0dh,0ah,0

.STACK 200
.CODE
main  PROC
   MOVQ mm0, QWORD PTR  BUF1
   MOVQ mm1,  QWORD PTR BUF2+2
   PMADDWD mm0,QWORD PTR BUF2+2
   MOVQ    QWORD PTR BUF3, mm0
   MOV     EAX,  BUF3
   ADD     EAX,  BUF3+4
   EMMS
   invoke printf,offset lpFmt, EAX,EAX
   invoke Exitprocess, 0
main  ENDP
END
