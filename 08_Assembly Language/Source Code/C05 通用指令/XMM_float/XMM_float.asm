.XMM
.model flat, stdcall
  ExitProcess PROTO STDCALL :DWORD
  includelib  kernel32.lib
  includelib  msvcrt.lib
  printf      PROTO C :ptr sbyte, :VARARG
.DATA
  lpFmt	db	"%f",0ah, 0dh, 0
  X  REAL4  3.14
  Y  REAL4  5.701
  Z  REAL4  0.0
.STACK 200
.CODE
 START: 
   movss     XMM0, X
   addss     XMM0, Y
   MOVSS     Z,   XMM0
   cvtss2sd  XMM0, Z  
   SUB    ESP,  8
   MOVSD  mmword ptr [ESP], XMM0
   invoke printf,offset lpFmt
   invoke ExitProcess, 0
END START 