.686P
.model flat, stdcall
  ExitProcess PROTO STDCALL :DWORD
  includelib  kernel32.lib
 ; includelib      msvcrt.lib
  includelib  libcmt.lib
 includelib  legacy_stdio_definitions.lib
  printf          PROTO C :ptr sbyte, :VARARG
.DATA
  lpFmt	DB	"%s > %s ?  %d (0,=;  -1, < ; 1, >) ", 0dh,0ah,0
  string1  db 'hello',0
  string2  db 'very good',0
  string3  db 'hello',0
.STACK 200
.CODE
main  proc  c 
   PUSH  OFFSET string2
   PUSH  OFFSET string1
   CALL  STRCMP
   ADD   ESP, 8
   invoke printf,offset lpFmt, offset string1, offset string2, EAX

   PUSH  OFFSET string3
   PUSH  OFFSET string1
   CALL  STRCMP
   ADD   ESP, 8
   invoke printf,offset lpFmt, offset string1, offset string3, EAX
   invoke ExitProcess, 0
main  endp


; �ӳ��� STRCMP  str1  str2
; ���ܣ��Ƚ������ַ���str1��str2�Ĵ�С��ϵ��
; ��ڲ��������������׵�ַ�ڶ�ջ�У�str2���׵�ַ����ջ
; ���ڲ�����EAX, ��ǰ��С����Ϊ(EAX)=-1����ǰ����Ϊ1�����Ϊ0
; �㷨˼�룺�Ӵ�������˿�ʼ���ң���һ�Ƚ���������Ӧ���ַ��Ĺ�ϵ
;           ��������Ӧ�ַ�����ȣ���ȽϽ����������������ַ��Ĵ�С��ϵ���������Ĵ�С��ϵ��
;           ��������Ӧ�ַ���ȣ����Ҳ��Ǵ��Ľ�����0������������ұȽϣ�����0���򷵻ش���ȡ�
; �Ĵ������䣺
;           EDI, ָ�� str1�� �� (EDI)Ϊ��str1�д��Ƚ��ַ��ĵ�ַ
;           ESI, ָ�� str2�� �� (ESI)Ϊ��str2�д��Ƚ��ַ��ĵ�ַ
;           DL, ���ڻ��浱ǰ��ȡ�����ַ�
STRCMP PROC
    PUSH  EBP
	MOV   EBP, ESP
	PUSH  ESI
	PUSH  EDI
	PUSH  EDX
	MOV   EDI, [EBP+8]
	MOV   ESI, [EBP+12]
STRCMP_L1: 
    MOV   DL,  [EDI]
	CMP   DL,  [ESI]
	JA    STRCMP_LARGE
	JB    STRCMP_LITTLE
	CMP   DL, 0
	JZ    STRCMP_EQU
	INC   ESI
	INC   EDI
	JMP   STRCMP_L1
STRCMP_LARGE:
    MOV   EAX, 1
	JMP   STRCMP_EXIT
STRCMP_LITTLE:
    MOV   EAX, -1
	JMP   STRCMP_EXIT
STRCMP_EQU:
    MOV   EAX, 0
STRCMP_EXIT:
    POP   EDX
	POP   EDI
	POP   ESI
    POP   EBP
	RET    
STRCMP ENDP
END  