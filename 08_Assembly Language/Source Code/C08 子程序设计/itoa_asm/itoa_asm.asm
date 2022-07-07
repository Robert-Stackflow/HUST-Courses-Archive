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

; 子程序 ITOA  VALUE, STRING, RADIX
; 功能：将一个有符号数转换成指定基数的串，结果存放在以 STRING为首址的缓冲区中
; 入口参数：从右到左用堆栈传递的三个参数
; 出口参数：无
; 算法思想：除基数取余法
; 寄存器分配：
;           (EDX，EAX) 作为被除数, 在除法运算后，EAX存放商，EDX存放余数
;           (EBX) 除数
;           (ECX) 转换出的字符个数
;           (ESI) 存放转换结果的地址
ITOA PROC
    PUSH  EBP
	MOV   EBP, ESP
	PUSH  EAX
	PUSH  EBX
	PUSH  ECX
	PUSH  EDX
	PUSH  ESI
	MOV   EAX, [EBP+8]    ; 待转换的数
	MOV   ESI, [EBP+12]   ; 存放结果的缓冲区地址
	MOV   EBX, [EBP+16]   ; 基数
	MOV   ECX, 0          ; 转换出的字符个数
	CMP   EAX, 0
	JGE   ITOA_UNSIGNED
	NEG   EAX             ; 对负数，输出负号，并且转换成其相反数的补码
	MOV   BYTE PTR [ESI], '-'
	INC   ESI
ITOA_UNSIGNED:      ; 下面是对一个无符号数(EAX)转换
    MOV   EDX, 0
	DIV   EBX
	PUSH  EDX       ; 保存余数，最先计算出来的是最右端的数
	INC   ECX
	CMP   EAX, 0
	JNE   ITOA_UNSIGNED
ITOA_SAVE:      ; 下面将堆栈中记录的各数取出，转换成ASCII，并且送到缓冲区中
                ;  ECX的初值肯定是大于0的。即使对数值0，也有一个数码0放入堆栈中了。 
    POP   EDX
	CMP   DL, 10
	JB    ITOA_CONVERT
	ADD   DL, 7   ; 对于0-9之间的数码直接加30H，变成对应的ASCII
	              ; 对于 A-F之间的数码，要加 37H ，即  数码-10+'A'(41H)
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