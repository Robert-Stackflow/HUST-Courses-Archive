;.XMM
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
   MOVSS     Z,   XMM0
   cvtss2sd  XMM0, Z  
   SUB    ESP,  8
   MOVSD  mmword ptr [ESP], XMM0
   invoke printf,offset lpFmt
   invoke ExitProcess, 0
main endp
end