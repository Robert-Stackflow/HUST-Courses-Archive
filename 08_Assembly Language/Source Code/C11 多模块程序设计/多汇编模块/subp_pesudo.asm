.686P
.model flat, C
.CODE
; SORT ����һ��˫�����͵����鰴��С�����˳������
; BUF  : ���뻺�������׵�ַ��Ҳ����������ŵ��׵�ַ
; NUM  : Ԫ�صĸ���
SORT_PESUDO  PROC BUF:DWORD, NUM:DWORD
   LOCAL   OUTLOOP_NUM:DWORD
   .if (NUM<2)
       RET
   .endif
   MOV  EAX, NUM
   DEC  EAX
   MOV  OUTLOOP_NUM, EAX  ; ��ѭ���Ĵ���
   MOV  EBX, BUF  ; ���ݻ��������׵�ַ�� EBX��
   MOV  ESI, 0    ; ��ѭ���Ŀ���ָ��
   .while (ESI < OUTLOOP_NUM)
              ; ��������ѭ��
       LEA  EDI, [ESI+1]
	   MOV  EAX, [EBX][ESI*4]
       .WHILE (EDI < NUM) 
		   .IF   EAX >= SDWORD PTR [EBX][EDI*4]
		         XCHG EAX, [EBX][EDI*4]
		   .ENDIF
	       INC  EDI
	 .endw
	 MOV  [EBX][ESI*4],EAX
	 INC  ESI
   .ENDW
   RET
SORT_PESUDO ENDP

END 

