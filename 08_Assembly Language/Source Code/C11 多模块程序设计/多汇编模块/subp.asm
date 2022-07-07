.686P
.model flat, C
;  includelib      msvcrt.lib
  printf          PROTO :VARARG

extern  lpFmt:sbyte

.CODE
; SORT ����һ��˫�����͵����鰴��С�����˳������
; BUF  : ���뻺�������׵�ַ��Ҳ����������ŵ��׵�ַ
; NUM  : Ԫ�صĸ���
SORT  PROC BUF:DWORD, NUM:DWORD
   LOCAL   OUTLOOP_NUM:DWORD
   .IF (NUM<2)
       RET
   .ENDIF
   MOV  EAX, NUM
   DEC  EAX
   MOV  OUTLOOP_NUM, EAX  ; ��ѭ���Ĵ���
   MOV  EBX, BUF  ; ���ݻ��������׵�ַ�� EBX��
   MOV  ESI, 0    ; ��ѭ���Ŀ���ָ��
Out_Loop:    ; ��ѭ��
   CMP  ESI, OUTLOOP_NUM
   JAE  EXIT
              ; ��������ѭ��
   LEA  EDI, [ESI+1]
   Inner_Loop:
         CMP  EDI, NUM
		 JAE  Inner_Loop_Over
		 MOV  EAX, [EBX][ESI*4]
		 CMP  EAX, [EBX][EDI*4]
		 JLE  Inner_Modify
		 XCHG EAX, [EBX][EDI*4]
		 MOV  [EBX][ESI*4], EAX
	Inner_Modify:   ; �޸���ѭ���Ŀ��Ʊ���
	     INC  EDI
		 JMP  Inner_Loop
	Inner_Loop_Over:
	INC  ESI
	JMP  Out_Loop
EXIT:
	RET
SORT ENDP

DISPLAY PROC BUF:DWORD, NUM:DWORD
	MOV  ECX,NUM
	MOV  EBX, BUF
   .WHILE (NUM>0)
    invoke printf,offset lpFmt, DWORD PTR [EBX]
	ADD  EBX,4
	DEC  NUM
   .ENDW
   RET
DISPLAY ENDP
END 

