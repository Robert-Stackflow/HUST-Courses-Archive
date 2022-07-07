.686P
.model flat, stdcall
  ExitProcess proto :dword
  includelib  kernel32.lib
;  includelib  msvcrt.lib
 includelib  libcmt.lib
 includelib  legacy_stdio_definitions.lib
  putchar     proto c :byte  ;	显示给定 ASCII 对应的字符
.stack 200
.code
main proc c 
   call  display
   msg1  db 'Very Good',0DH,0AH,0
   call  display
   msg2  db '12345',0DH,0AH,0
   invoke ExitProcess, 0
main  endp
; _________________________________
; 子程序：显示一个字符串 
display proc
   pop  ebx
p1:
   cmp  byte ptr [ebx],0
   je   exit
   invoke  putchar, byte ptr [ebx] 
   inc  ebx
   jmp  p1
exit:
   inc  ebx
   push ebx
   ret   
display endp
end