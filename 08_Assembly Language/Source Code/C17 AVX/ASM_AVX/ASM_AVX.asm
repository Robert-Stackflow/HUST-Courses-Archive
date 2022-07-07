.686P
.XMM
.model flat, c

  ExitProcess PROTO STDCALL :DWORD
 ; includelib      msvcrt.lib
  printf          PROTO  :VARARG
  includelib  libcmt.lib
 includelib  legacy_stdio_definitions.lib
;  includelib libvcruntime.lib
;  includelib libucrt.lib



.DATA
  lpFmt	db	"%f",0ah, 0dh, 0
  X  REAL4  3.14
  Y  REAL4  5.701
  Z  REAL4  0.0
.STACK 200
.CODE
main  proc
 ;  MOV EAX,1
;   CPUID
   vmovss xmm0, X
   vaddss xmm0,xmm0, y  ; DWORD PTR Y
   vmovss Z, xmm0
   vcvtss2sd xmm0, xmm0, z
 ;  cvtss2sd xmm0,Z
   sub  ESP,8
   vmovsd	QWORD PTR [esp], xmm0
   invoke printf,offset lpFmt
;   add  esp,8
 ;  invoke Exitprocess, 0
 ret
main endp
end
