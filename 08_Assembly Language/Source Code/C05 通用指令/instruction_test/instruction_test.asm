.686P
.model flat, c
  ExitProcess PROTO STDCALL :DWORD
  includelib  kernel32.lib
  includelib      msvcrt.lib
  printf          PROTO C :ptr sbyte, :VARARG
 
.DATA
  lpFmt	db	"%d",0ah, 0dh, 0
  T1 DD -33
  T2 SDWORD -33
  X  DD  10 DUP(0)
  P  DD  L1
  bv db  1,2,3,4
.STACK 200
.CODE
 START: 
MOV AL,37H
MOV BL,35H
ADD AL,BL
stc
dAA

MOV Ax,3737H
MOV Bx,3535H
ADD Ax,Bx
AAA
 lea eax, [ebx+ecx]
 mov eax,ebx
 push 1234h
 mov  eax,00

   mov   eax,1234h
   mov   ebx,4567h
   mov   ecx,1122h
   lea   ebx,bv
   RDSEED ebx
   RDRAND eax

 ;  xsave X

   cmp   eax, 1235h   

   sete  byte ptr [ebx]

   cmove ax, [ebx]
   JMP   L1
   MOV   EBX, P
   JMP   EBX
   JMP   P
   MOV   EBX, OFFSET P
   JMP   DWORD PTR [EBX]
 L1:
   invoke printf,offset lpFmt,eax
   invoke ExitProcess, 0
END START 