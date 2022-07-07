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
  STRING   DB   '123',0
.STACK 200
.CODE
; START: 
main PROC C  
   PUSH  OFFSET STRING
   CALL  ATOI
   ADD   ESP, 4
   MOV   VALUE, EAX
   invoke printf,offset lpFmt, offset  STRING, VALUE 
   invoke ExitProcess, 0
main ENDP

; �ӳ��� ATOI  STRING
; ���ܣ���һ�������������ŵ�����ASCII��ת��Ϊһ��������
; ��ڲ�������ת�������׵�ַ
; ���ڲ�����EAX
; �㷨˼�룺ѭ���Ը����봦��������һ��������ʱ����ǰ��ת���Ľ����10Ȼ���ټӵ�ǰ����
; �Ĵ������䣺
;           EAX ���ת�����
;           EBX ����������Ϣ EBX=1����ʾ�и��ţ�Ϊ0�����ʾΪ��
;           EDX ��ǰ����������
;           ESI ��ǰ����ĵ�ַ
ATOI PROC
    PUSH  EBP
	MOV   EBP, ESP
	PUSH  EBX
	PUSH  EDX
	PUSH  ESI
	MOV   ESI, [EBP+8]    ; ��ת�������׵�ַ
	MOV   EAX, 0
	MOV   EBX, 0
	CMP   BYTE PTR [ESI], '-'
	JNZ   ATOI_NOTS
    MOV   EBX,  1
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
	CMP   EBX, 1
	JNZ   ATOI_OVER
	NEG   EAX
ATOI_OVER:
	POP   ESI
    POP   EDX
	POP   EBX
    POP   EBP
	RET    
ATOI ENDP
END