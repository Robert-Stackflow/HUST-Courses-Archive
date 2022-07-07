;.686P  ;处理器选择伪指令,支持80387数学协处理器指令
.387
.model flat, stdcall
  ExitProcess PROTO STDCALL :DWORD
  includelib  kernel32.lib
;  includelib  msvcrt.lib
  printf      PROTO C :ptr sbyte, :VARARG
   includelib  libcmt.lib
 includelib  legacy_stdio_definitions.lib
.DATA
  lpFmt	db	"%f",0ah, 0dh, 0
  X  REAL4  3.14
  Y  REAL4  5.701
  Z  REAL4  0.0
.STACK 200
.CODE
 main  proc c 
   fld    X   ; 将变量X中的内容压入 FPU数据寄存器栈的栈顶ST(0)
   fadd   Y   ; (ST(0))+(Y)->ST(0)
   fst    Z   ; (ST(0))->Z
   sub    ESP,  8
   fstp  qword ptr [ESP]  ; (ST(0))转换成4字类型，送到内存堆栈中
   invoke printf,offset lpFmt
   invoke ExitProcess, 0
main  endp

END
