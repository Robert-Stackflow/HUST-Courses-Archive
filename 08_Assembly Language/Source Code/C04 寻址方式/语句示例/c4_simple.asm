.686P     

.model flat, stdcall
 ExitProcess PROTO STDCALL :DWORD
 includelib  kernel32.lib  ; ExitProcess �� kernel32.lib��ʵ��
 printf          PROTO C :VARARG
 includelib  libcmt.lib
 includelib  legacy_stdio_definitions.lib

.DATA
X   DD 12345678H
 lpFmt	db	"%d",0ah, 0dh, 0
.STACK 200
.CODE
main proc c
   mov ax, [EBX]
 
   add X,EBX
   add X,11223344H
   mov al,[ebx]
   mov al,11H
   mov [ebx],al
   mov ah,[ebx]


  add  ebx,dword ptr [ecx] ; ��������8B 19
add  bx,word ptr [ecx]   ; �������� 66 8B 19 ��ǰ׺66H,��ʾ����16λ�Ĵ��� 
add  bl,byte ptr [ecx]

   mov eax,[EBX]
   MOV EBX, X
   MOV X,  EBX
   MOV X, 0
   MOV EAX,12H 
   MOV EAX,-12H
   MOV EAX, 0FFFFFFEEH  
   MOV AX, -12H
   MOV AL, -12H 
   MOV EAX, 3*4+5*6
   MOV AL, '1'
   MOV AX,'12'
  
   MOV EAX,'1234'

 ;  MOV EAX, 0FFFFFEEH  
   MOV EBX,offset x
   LEA ECX, X
   MOV EAX,[EBX] 
     
   CALL f1
   invoke printf,offset lpFmt,eax
   invoke ExitProcess, 0
main endp

f1 proc
   LOCAL y:WORD
   LEA BX, y

 
   RET
 f1 endp
END