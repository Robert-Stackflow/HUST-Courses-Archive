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

; 子程序 ATOI  STRING
; 功能：将一个含有正、负号的数字ASCII串转换为一个整型数
; 入口参数：待转换串的首地址
; 出口参数：EAX
; 算法思想：循环对各数码处理，当读到一个新数码时，将前面转换的结果乘10然后再加当前数码
; 寄存器分配：
;           EAX 存放转换结果
;           EBX 正、负号信息 EBX=1，表示有负号，为0，则表示为正
;           EDX 当前读到的数码
;           ESI 当前数码的地址
ATOI PROC
    PUSH  EBP
	MOV   EBP, ESP
	PUSH  EBX
	PUSH  EDX
	PUSH  ESI
	MOV   ESI, [EBP+8]    ; 待转换串的首地址
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