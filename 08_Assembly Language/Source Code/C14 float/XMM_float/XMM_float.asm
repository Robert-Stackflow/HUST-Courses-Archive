.XMM
.model flat, stdcall
  ExitProcess PROTO STDCALL :DWORD
  includelib  kernel32.lib
  includelib  libcmt.lib   
  includelib  legacy_stdio_definitions.lib
  printf      PROTO C :ptr sbyte, :VARARG
.DATA
  lpFmt	db	"%f",0ah, 0dh, 0
  X  REAL4  3.14
  Y  REAL4  5.701
  Z  REAL4  0.0
.STACK 200
.CODE
main proc c
   movss     XMM0, X
   addss     XMM0, Y
   movss     Z,   XMM0
   cvtss2sd  XMM0, Z  
   sub    ESP,  8
   movsd  mmword ptr [ESP], XMM0
   invoke printf,offset lpFmt
   invoke ExitProcess, 0
main endp 
end

; 若将 Z 的定义该为 Z REAL8 0.0
; 程序改为
; movss     XMM0, X
;  addss     XMM0, Y
;  cvtss2sd    XMM0,XMM0
;  movsd      Z, XMM0
;  invoke printf,offset lpFmt,Z
