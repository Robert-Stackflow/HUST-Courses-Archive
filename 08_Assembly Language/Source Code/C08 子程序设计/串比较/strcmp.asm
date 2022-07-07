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


; 子程序 STRCMP  str1  str2
; 功能：比较两个字符串str1和str2的大小关系，
; 入口参数：两个串的首地址在堆栈中，str2的首地址先入栈
; 出口参数：EAX, 若前串小，则为(EAX)=-1，若前串大为1，相等为0
; 算法思想：从串的最左端开始向右，逐一比较两个串对应的字符的关系
;           若两个对应字符不相等，则比较结束，根据这两个字符的大小关系，决定串的大小关系；
;           若两个对应字符相等，并且不是串的结束（0），则继续向右比较；若是0，则返回串相等。
; 寄存器分配：
;           EDI, 指向 str1， 即 (EDI)为串str1中待比较字符的地址
;           ESI, 指向 str2， 即 (ESI)为串str2中待比较字符的地址
;           DL, 用于缓存当前读取到的字符
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