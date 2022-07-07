.386
.model flat, stdcall

; ExitProcess 在 kernel32.lib中实现，原型定义如下 
  ExitProcess PROTO STDCALL :DWORD
  includelib  kernel32.lib
 
 ; printf 在 msvcrt.lib中实现，原型定义如下
  includelib      msvcrt.lib
  printf          PROTO C :ptr sbyte, :VARARG
  scanf_s         PROTO C :ptr sbyte, :VARARG
 
.DATA
  lpFmt	db	"%d",0ah, 0dh, 0
  buf   db  "%d", 0
  x     dd  0
  
.STACK 200

.CODE
 START:  
   invoke scanf_s, offset buf, offset x
    
         ; eax=0; for (ebx=1;ebx<=x;ebx++) eax=eax+ebx;
   mov  eax, 0
   mov  ebx, 1
lp: cmp  ebx, x
   jg   exit
   add  eax, ebx
   add  ebx, 1
   jmp  lp
exit:
   invoke printf,offset lpFmt,eax
   invoke ExitProcess, 0
END START 