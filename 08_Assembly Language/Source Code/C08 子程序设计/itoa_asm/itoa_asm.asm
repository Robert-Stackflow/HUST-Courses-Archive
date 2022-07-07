.686P
.model flat, stdcall
  ExitProcess PROTO STDCALL :DWORD
  includelib  kernel32.lib
  includelib      msvcrt.lib
  printf          PROTO C :ptr sbyte, :VARARG
  includelib  libcmt.lib   
  includelib  legacy_stdio_definitions.lib

.DATA
  lpFmt	   DB	"%d > %s", 0dh,0ah,0
  VALUE    DD   123
  STRING   DB   20 dup(0)
  RADIX    DD   10
  func_table dd itoa

.STACK 200
.CODE
main proc  c
   PUSH  RADIX
   PUSH  OFFSET STRING
   PUSH  VALUE
;   CALL  ITOA
mov  eax, 0

   call func_table[eax]
   ADD   ESP, 12
   invoke printf,offset lpFmt, VALUE, offset  STRING
   invoke ExitProcess, 0
main endp

; �ӳ��� ITOA  VALUE, STRING, RADIX
; ���ܣ���һ���з�����ת����ָ�������Ĵ������������� STRINGΪ��ַ�Ļ�������
; ��ڲ��������ҵ����ö�ջ���ݵ���������
; ���ڲ�������
; �㷨˼�룺������ȡ�෨
; �Ĵ������䣺
;           (EDX��EAX) ��Ϊ������, �ڳ��������EAX����̣�EDX�������
;           (EBX) ����
;           (ECX) ת�������ַ�����
;           (ESI) ���ת������ĵ�ַ
ITOA PROC
    PUSH  EBP
	MOV   EBP, ESP
	PUSH  EAX
	PUSH  EBX
	PUSH  ECX
	PUSH  EDX
	PUSH  ESI
	MOV   EAX, [EBP+8]    ; ��ת������
	MOV   ESI, [EBP+12]   ; ��Ž���Ļ�������ַ
	MOV   EBX, [EBP+16]   ; ����
	MOV   ECX, 0          ; ת�������ַ�����
	CMP   EAX, 0
	JGE   ITOA_UNSIGNED
	NEG   EAX             ; �Ը�����������ţ�����ת�������෴���Ĳ���
	MOV   BYTE PTR [ESI], '-'
	INC   ESI
ITOA_UNSIGNED:      ; �����Ƕ�һ���޷�����(EAX)ת��
    MOV   EDX, 0
	DIV   EBX
	PUSH  EDX       ; �������������ȼ�������������Ҷ˵���
	INC   ECX
	CMP   EAX, 0
	JNE   ITOA_UNSIGNED
ITOA_SAVE:      ; ���潫��ջ�м�¼�ĸ���ȡ����ת����ASCII�������͵���������
                ;  ECX�ĳ�ֵ�϶��Ǵ���0�ġ���ʹ����ֵ0��Ҳ��һ������0�����ջ���ˡ� 
    POP   EDX
	CMP   DL, 10
	JB    ITOA_CONVERT
	ADD   DL, 7   ; ����0-9֮�������ֱ�Ӽ�30H����ɶ�Ӧ��ASCII
	              ; ���� A-F֮������룬Ҫ�� 37H ����  ����-10+'A'(41H)
ITOA_CONVERT:
    ADD   DL,  30H
	MOV   [ESI],DL
	INC   ESI
	DEC   ECX
	JNZ   ITOA_SAVE
	POP   ESI
    POP   EDX
	POP   ECX
	POP   EBX
	POP   EAX
    POP   EBP
	RET    
ITOA ENDP
END  