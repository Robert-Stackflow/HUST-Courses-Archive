.486
.model flat, stdcall
  ExitProcess PROTO STDCALL :DWORD
  includelib  kernel32.lib
  includelib  libcmt.lib   
  includelib  legacy_stdio_definitions.lib
  printf          PROTO C :ptr sbyte, :VARARG
 
.DATA
  lpFmt	db	"%f",0ah, 0dh, 0
  ControlWord DW 0
  X  REAL4    2.5
 ; X  REAL4  3.14
  Y  REAL4  5.701
  Z  REAL4  0.0
  ZZ REAL8  0.0
.STACK 200
.CODE
main proc c
; FLDCW ControlWord
 FLD  X
 FLD  Y
 FCMOVB ST(0),ST(2)

   FDIV  X
   FST   Z
   FST   ZZ
   SUB    ESP,  8
   fst  qword ptr [ESP]
   invoke printf,offset lpFmt
   invoke ExitProcess, 0
main endp
end