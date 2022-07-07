.387
.model flat, stdcall
  ExitProcess PROTO STDCALL :DWORD
  includelib  kernel32.lib
  printf          PROTO C :ptr sbyte, :VARARG
  scanf_s         PROTO C :ptr sbyte, :VARARG
  includelib      msvcrt.lib

.DATA
  ubv DB     5
  ubv1 BYTE  5
  sbv SBYTE  6
  uwv DW     7
  uwv1 WORD  7
  swv SWORD  8
  udwv DD    -45.25
  udwv1 DWORD -45.25
  sdwv SDWORD 10
  udq  DQ     11
  udq1 QWORD  11
  f1   REAL4  -45.25
  f2   REAL8  -45.25
  	lpFmt	db	"%f",0ah, 0dh, 0
.STACK 200
.CODE
 START:  
 ;   FINIT
 ;   FLD udwv
 mov ubv1,20
 .if sbv>5
     mov eax,0
 .endif
    mov  eax,udwv
	invoke printf,offset lpFmt,EAX
    invoke ExitProcess, 0
END START 