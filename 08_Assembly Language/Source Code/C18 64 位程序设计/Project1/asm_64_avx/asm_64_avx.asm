  extern ExitProcess :proc
  includelib      msvcrt.lib
  extern printf   :proc
.data
  lpFmt	db	"%f",0ah, 0dh, 0
  x  real4  3.14
  y  real4  5.701
  z  real4  0.0
.code
mainp  proc
   vmovss xmm0, x
   vaddss xmm0,xmm0, dword ptr y
   vmovss z, xmm0
   cvtss2sd xmm0, z
   movd rdx, xmm0
   lea  rcx, lpFmt
   sub  rsp, 28h
   call printf
   add  rsp,28h
   mov  rcx,0
   call Exitprocess
mainp  endp
end