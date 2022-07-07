 .686P
.model flat, stdcall
option casemap:none

ExitProcess PROTO return:DWORD
 includelib  kernel32.lib
;  includelib      msvcrt.lib
; printf          PROTO C :ptr sbyte, :VARARG
 ; extern printf:NEAR

  includelib  libcmt.lib
 ; includelib libvcruntime.lib
 ; includelib libucrt.lib
  includelib     legacy_stdio_definitions.lib

;  includelib     legacy_stdio_wide_specifiers.lib
  ; legacy_stdio_definitions.lib
printf PROTO C :vararg

.DATA
  lpFmt	   DB	"%s > %d", 0dh,0ah,0
  VALUE    DD   0
  STRING   DB   '-123',0
.STACK 200
.CODE

 main PROC C
   PUSH  OFFSET STRING
   CALL  ATOI
   ADD   ESP, 4

   PUSH  100
   CALL  LOCAL_VARIABLE
   ADD   ESP, 4

   MOV   VALUE, EAX
   invoke printf,offset lpFmt, offset  STRING, VALUE 
   invoke ExitProcess, 0
   RET
   main ENDP

   LOCAL_VARIABLE PROC
     LOCAL FLAG:DWORD
	 PUSH  EBX
	 MOV   EBX, [EBP+8]
	 MOV   FLAG,EBX
	 MOV   FLAG[EBX],0
;	 MOV   FLAG[EBX+ECX],0
	 POP   EBX
	 RET
LOCAL_VARIABLE ENDP

; �ӳ��� ATOI  STRING
; ���ܣ���һ�������������ŵ�����ASCII��ת��Ϊһ��������
; ��ڲ�������ת�������׵�ַ
; ���ڲ�����EAX
; �㷨˼�룺���ִ�ǰ����������
;           ����ֲ����� FLAG, FLAG=1����ʾ�и��ţ�Ϊ0��1���ʾΪ�޷���
;           �����ִ�����һ���޷���������ѭ���Ը����봦��
;           ������һ��������ʱ����ǰ��ת���Ľ����10Ȼ���ټӵ�ǰ����
;           ��������������ж����޷��ţ����ڸ�������ǰ���������Ĳ��뼴�ɡ�
; �Ĵ������䣺
;           EAX ���ת�����
;           EDX ��ǰ����������
;           ESI ��ǰ����ĵ�ַ

ATOI PROC
    LOCAL FLAG:BYTE
;    PUSH  EBP
;  MOV   EBP, ESP
	PUSH  EBX
	PUSH  EDX
	PUSH  ESI
	MOV   ESI, [EBP+8]    ; ��ת�������׵�ַ
	MOV   EAX, 0
	MOV   FLAG, 0         ; FLAG=0����ת���Ĵ�ǰ�޸���
	CMP   BYTE PTR [ESI], '-'
	JNZ   ATOI_NOTS
    MOV   FLAG,  1        ; FLAG=1����ת���Ĵ�ǰ�и���
	INC   ESI
	JMP   ATOI_CONVERT
ATOI_NOTS:
	CMP   BYTE PTR [ESI], '+'
	JNZ   ATOI_CONVERT
	INC   ESI
ATOI_CONVERT:
    MOV   DL, [ESI]
	CMP   DL, 0
	JZ    ATOI_CONVERT_OVER
	SUB   DL, 30H
	MOVZX EDX,DL
	IMUL  EAX, 10
	ADD   EAX, EDX
	INC   ESI
	JMP   ATOI_CONVERT
ATOI_CONVERT_OVER:
	CMP   FLAG, 1
	JNZ   ATOI_OVER
	NEG   EAX
ATOI_OVER:
	POP   ESI
    POP   EDX
	POP   EBX
;    POP   EBP
	RET    
ATOI ENDP

END 