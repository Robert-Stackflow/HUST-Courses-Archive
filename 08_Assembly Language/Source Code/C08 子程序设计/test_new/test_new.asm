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

; 子程序 ATOI  STRING
; 功能：将一个含有正、负号的数字ASCII串转换为一个整型数
; 入口参数：待转换串的首地址
; 出口参数：EAX
; 算法思想：区分串前有无正负号
;           定义局部变量 FLAG, FLAG=1，表示有负号，为0，1则表示为无符号
;           将数字串当成一个无符号数串，循环对各数码处理；
;           当读到一个新数码时，将前面转换的结果乘10然后再加当前数码
;           当数串读完后，再判断有无符号，对于负数，求前面所求结果的补码即可。
; 寄存器分配：
;           EAX 存放转换结果
;           EDX 当前读到的数码
;           ESI 当前数码的地址

ATOI PROC
    LOCAL FLAG:BYTE
;    PUSH  EBP
;  MOV   EBP, ESP
	PUSH  EBX
	PUSH  EDX
	PUSH  ESI
	MOV   ESI, [EBP+8]    ; 待转换串的首地址
	MOV   EAX, 0
	MOV   FLAG, 0         ; FLAG=0，待转换的串前无负号
	CMP   BYTE PTR [ESI], '-'
	JNZ   ATOI_NOTS
    MOV   FLAG,  1        ; FLAG=1，待转换的串前有负号
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