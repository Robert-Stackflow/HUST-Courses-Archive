.686P
.model flat, c
  ExitProcess PROTO STDCALL :DWORD
 ; includelib  kernel32.lib
  includelib  libcmt.lib   
  includelib  legacy_stdio_definitions.lib
  printf          PROTO  :ptr sbyte, :VARARG
  clock           PROTO 
  getchar         PROTO 
  
.DATA
  lpFmt	      DB	"%d", 0dh,0ah,0
  buf1        DB   10000 DUP(0)
  buf2        DB   10000 DUP (1)
  begin_time  DD   0
  end_time    DD   0
  spend_time  DD   0         ; 运行时间(豪秒)
.STACK 200
METHOD1 MACRO
L2:   
   MOV    EAX, [ESI]
   MOV    [EDI],EAX
   ADD    ESI,4
   ADD    EDI,4
;   MOV    AL, [ESI]
;   MOV    [EDI],AL
;   ADD    ESI, 1
;   ADD    EDI, 1
   DEC    ECX
   JNZ    L2
   ENDM


.CODE
main  proc
   invoke clock
   MOV    BEGIN_TIME, EAX
   MOV    EBX, 20000
L:
   LEA    ESI, BUF1
   LEA    EDI, BUF2
   MOV    ECX, 10000/4
   CLD
   ; REP    MOVSd
   L2:
     MOVSB
	 DEC ECX
	 JNZ L2
;   METHOD1
   DEC    EBX
   JNZ    L
   invoke clock
   MOV    END_TIME, EAX
   SUB    EAX, BEGIN_TIME
   MOV    SPEND_TIME, EAX
   invoke printf,offset lpFmt, EAX
   invoke getchar
   invoke Exitprocess, 0
main endp
end