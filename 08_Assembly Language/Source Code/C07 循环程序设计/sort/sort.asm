.686P
.model flat, c
  ExitProcess PROTO STDCALL :DWORD
  includelib  kernel32.lib
  includelib  libcmt.lib
  includelib  legacy_stdio_definitions.lib
  printf      PROTO  :ptr sbyte, :VARARG
.DATA
  lpFmt	DB	"%d ", 0
  BUF  DD   -10, 20, 30,-100, 25, 60
  N    =  ($-BUF)/4
.STACK 200
.CODE
main  proc
   MOV  ESI, 0
Out_Loop:    ; ��ѭ��
   CMP  ESI, N-1
   JAE  EXIT
        ; ��������ѭ��
   LEA  EDI, [ESI+1]
   Inner_Loop:
         CMP  EDI, N
		 JAE  Inner_Loop_Over
		 MOV  EAX, BUF[ESI*4]
		 CMP  EAX, BUF[EDI*4]
		 JLE  Inner_Modify
		 XCHG EAX, BUF[EDI*4]
		 MOV  BUF[ESI*4], EAX
	Inner_Modify:   ; �޸���ѭ���Ŀ��Ʊ���
	     INC  EDI
		 JMP  Inner_Loop
	Inner_Loop_Over:
	INC  ESI
	JMP  Out_Loop

EXIT:  ; ��ѭ��������
    MOV  ESI, 0
DISPLAY:
	CMP  ESI, N
	JAE  Program_Over
    invoke printf,offset lpFmt, BUF[ESI*4], 20*30
	INC  ESI
	JMP  DISPLAY
Program_Over:
   invoke ExitProcess, 0
main  endp

END 