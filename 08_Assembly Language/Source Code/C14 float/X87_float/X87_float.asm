.686P
.XMM
;.387
.model flat, stdcall
  ExitProcess PROTO STDCALL :DWORD
  includelib  kernel32.lib
  includelib  libcmt.lib   
  includelib  legacy_stdio_definitions.lib
  printf      PROTO C :ptr sbyte, :VARARG
.DATA
  lpFmt	db	"%f",0ah, 0dh, 0
  ZZZ  DD  10
  B1   DB  1
  B2   DW  1
  B4   DD  1
  B8   DQ  1
  F1 REAL4  1.25
  I2 DQ  1.2
  FF2 REAL8 1.2
  F2 REAL8 1.55
  F3 REAL4 1.25
  F10 REAL10 1.25
  T10 DT     1.25
  X  REAL4  3.14
  Y  REAL4  5.701
  Z  REAL8  0.0
.STACK 200
.CODE
main proc c
fld F1
fld F2
fcompP 
fmul  st(1),st(0)
fsubr st(0),st(1)
faddp ST(1),ST(0)
fadd ST(0),ST(1)

fld f10
fld F1
fld F2
fld f10
fld FF2
   fld      F1
   fld      ST(3)
   fld      F2
   fxch     ST(2)
   fmul     Y
   fadd     Y
   fstp     Z
;   SUB    ESP,  8   
;   fld    Z
;   fstp  qword ptr [ESP]
;   invoke printf,offset lpFmt
     ;  printf 中打印的浮点数%f是 8字节， 
	 ;  若将Z定义为 REAL4，则用上面注释的形式, 否则，用下面的形式，显示结果不对
	 ;  中间有一个4字节浮点向8字节浮点转换的问题
   invoke printf,offset lpFmt,Z
   invoke ExitProcess, 0
main endp
end