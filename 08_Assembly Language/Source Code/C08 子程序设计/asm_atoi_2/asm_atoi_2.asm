.686P
.model flat, stdcall
;option casemap:none

includelib libcmt.lib
includelib libvcruntime.lib
includelib libucrt.lib
includelib legacy_stdio_definitions.lib

ExitProcess PROTO :DWORD
printf PROTO C :vararg
.data
text BYTE "Text %d", 0
  lpFmt	   DB	"%s > %d", 0dh,0ah,0
  VALUE    DD   0
  STRING   DB   '123',0

.code
main PROC  C                   ; Specify "C" calling convention
   PUSH  OFFSET STRING
   CALL  ATOI
   ADD   ESP, 4

;    push  120
;    push offset text
;   call printf
 ;  add  esp, 4	
   invoke printf, offset lpFmt,offset STRING,eax
 
   invoke ExitProcess,0       ; Since the C library called main (this function)
                               ; we can set eax to 0 and use ret`to have
                               ; the C runtime close down and return our error
                               ; code instead of invoking ExitProcess
 ;   mov eax, 0
 ;   ret
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




end                           ; Use `end` on a line by itself
                               ; We don't want to use `end main` as that would
                               ; make this function our program entry point
                               ; effectively skipping by the C runtime initialization