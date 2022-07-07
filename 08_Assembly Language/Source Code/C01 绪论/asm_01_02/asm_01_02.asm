; 教材 P11 例 1.2
; 输入5个有符号数到一个数组缓冲区中，
; 然后求它们的最大值并显示该最大值。
.686P
.model flat, c
  ExitProcess proto stdcall :dword
  includelib  kernel32.lib
  printf      proto  :ptr sbyte, :vararg
  scanf       proto  :ptr sbyte, :vararg
 includelib   libcmt.lib
 includelib   legacy_stdio_definitions.lib

.DATA
  lpFmt	db	"%d",0ah, 0dh, 0
  buf   db  "%d", 0
  x     dd  5 dup(0)
.STACK 200
.CODE
main proc 
    ; 输入5个数  ebx=0;  do { scanf("%d",&x[ebx*4]); ebx++; }while (ebx!=5)
   mov   ebx, 0
input_5num:
   invoke scanf, offset buf,  addr [x+ebx*4]
   inc    ebx
   cmp    ebx, 5
   jne    input_5num
   ; 求5个数中的最大数。先将第一个数作为最大数，放在eax中。      
   ; eax=x[0]; for (ebx=1;ebx<=4;ebx++) 
   ;             if (eax<x[ebx*4])  eax = x[ebx*4];
   mov  eax, x[0]
   mov  ebx, 1
lp: cmp  ebx, 4
   jg   exit
   cmp  eax, x[ebx*4]
   jge  next
   mov  eax, x[ebx*4]
next:
   add  ebx, 1
   jmp  lp
exit:
   invoke printf,offset lpFmt,eax
   invoke ExitProcess, 0
   main endp
end