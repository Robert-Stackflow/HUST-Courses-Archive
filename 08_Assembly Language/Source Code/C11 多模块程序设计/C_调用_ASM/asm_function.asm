.686P
.model flat, C
public y
public SORT_PESUDO
printf proto c  :vararg

.DATA
  y  SDWORD 300
  lpfmt db '%s',0dh,0ah,0
  msg   db 'good in asm',0
.CODE

; SORT ����һ��˫�����͵����鰴��С�����˳������
; BUF  : ���뻺�������׵�ַ��Ҳ����������ŵ��׵�ַ
; NUM  : Ԫ�صĸ���

SORT_PESUDO  PROC BUF:DWORD, NUM:DWORD
   LOCAL   OUTLOOP_NUM:DWORD
   invoke printf, offset lpfmt,offset msg
   .IF (NUM<2)
       RET
   .ENDIF
   MOV  EAX, NUM
   DEC  EAX
   MOV  OUTLOOP_NUM, EAX  ; ��ѭ���Ĵ���
   MOV  EBX, BUF  ; ���ݻ��������׵�ַ�� EBX��
   MOV  ESI, 0    ; ��ѭ���Ŀ���ָ��
   .WHILE (ESI < OUTLOOP_NUM)
              ; ��������ѭ��
       LEA  EDI, [ESI+1]
	   MOV  EAX, [EBX][ESI*4]
       .WHILE (EDI < NUM) 
		   .IF   EAX >= SDWORD PTR [EBX][EDI*4]
		         XCHG EAX, [EBX][EDI*4]
		   .ENDIF
	       INC  EDI
	 .ENDW
	 MOV  [EBX][ESI*4],EAX
	 INC  ESI
   .ENDW
   RET
SORT_PESUDO ENDP

extern x:sdword
modify_in_asm  PROC 
   mov  x,   100
   mov  x[1*TYPE SDWORD],200
   RET
modify_in_asm ENDP

END 

