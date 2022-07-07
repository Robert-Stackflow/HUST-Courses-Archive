.686P
.XMM
.model flat,c
ExitProcess PROTO STDCALL :DWORD
.data
yyy  db 0
align 16
SF1  REAL4  15.67,1.34,1.78,2.56
SF2  REAL4  3.5 , 4.7, 1.6, 2.0
SF3  REAL4  1.2,  2.3,  3.4, 4.5
W1   DW    1,2,3,4,5,6,7,8
W2   DW    2,3,4,5,6,7,8,9
W3   DW   100

B1   DB    200,15 DUP(1)
B2   DB    100,15 DUP(2)

RRR  SQWORD 8 DUP(0)
.stack 200
.code
start:
   movq  mm0, qword ptr w1
   movq  mm1, qword ptr w2
   psrlw mm0, 1
   psrlw mm0,1 
   punpckhbw mm0,mm1

   pmulhw mm0,mm1

   movdqu Xmm0, xmmword ptr W1
   movdqu xmm1, xmmword ptr W2
   pmullw xmm0,xmm1

MOV EAX,12345678H
   MOVQ   mm0, Qword ptr W1
   MOVQ   mm1, Qword ptr W2

   PSADBW mm0,mm1

   PMOVMSKB EAX,mm0
   PINSRW mm0,W3, 3
   PEXTRW EAX, mm0,1
   pAVGW  mm0,mm1

   movaps Xmm0 ,SF1
   movaps xmm1, xmmword ptr SF1
   movaps xmm1, SF2
   UNPCKHPS XMM0, XMM1

   SHUFPS  XMM0,XMM1,11100100B

   CVTSS2SI EAX, SF1
   movaps Xmm0 ,SF1
   movaps xmm1, SF2
 

   cmpss  xmm0, sF1,0
   
   cmpeqps Xmm0,Xmm1

   maxps  xmm0,xmm1


   movdqu xmm0,xmmword ptr B1    ; SSE2 ЦёБо
   movdqu xmm1,xmmword ptr B2
   paddusb  xmm0, xmm1
   paddusb  mm0,  mm1

   movdqu xmm0,xmmword ptr W1    ; SSE2 ЦёБо
   movdqu xmm1,xmmword ptr W2
   paddw  xmm0, xmm1

   movaps Xmm0 ,SF1
   MOVSS  XMM0,SF1
   movlps QWORD PTR SF3, XMM0

	invoke ExitProcess, 0


end start
