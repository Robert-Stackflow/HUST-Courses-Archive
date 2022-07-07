.686P
.model flat, stdcall
  ExitProcess PROTO STDCALL :DWORD
 ; includelib      msvcrt.lib  ;  老版本的库文件
  includelib  libcmt.lib   
  includelib  legacy_stdio_definitions.lib
  printf          PROTO C :ptr sbyte, :VARARG
  clock           PROTO C
  getchar         PROTO C
.DATA
  lpFmt	      DB	"%d (ms)", 0dh,0ah,0
  buf1        DB   10000 DUP(0)
  buf2        DB   10000 DUP (1)
  begin_time  DD   0
  end_time    DD   0
  spend_time  DD   0         ; 运行时间(豪秒)
.STACK 200
.CODE
main  PROC  c
   invoke clock
   MOV    BEGIN_TIME, EAX
   MOV    EBX, 20000
L:
   LEA    ESI, BUF1
   LEA    EDI, BUF2
   MOV    ECX, 10000
   CLD
   REP    MOVSB
   DEC    EBX
   JNZ    L
   invoke clock
   MOV    END_TIME, EAX
   SUB    EAX, BEGIN_TIME
   MOV    SPEND_TIME, EAX
   invoke printf,offset lpFmt, SPEND_TIME
   invoke getchar
   invoke ExitPRocess, 0
main  ENDP
END