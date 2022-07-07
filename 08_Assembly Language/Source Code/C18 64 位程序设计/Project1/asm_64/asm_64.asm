
;.model flat, stdcall    ; X64 不能使用 model 
 ;ExitProcess PROTO STDCALL :DWORD    ; X32 的使用方式，不再用堆栈传递参数
 ;ExitProcess PROTO STDCALL
 extern ExitProcess:proc
 
; includelib  kernel32.lib  ; ExitProcess 在 kernel32.lib中实现
 printf          PROTO C :VARARG
  ;printf          PROTO C    
; extern printf:near
   includelib  libcmt.lib
;  includelib libvcruntime.lib
;  includelib libucrt.lib
;  includelib     legacy_stdio_definitions.lib

; includelib      msvcrt.lib  ; printf 在 msvcrt.lib中实现
.DATA
 lpFmt	db	"%d",0ah, 0dh, 0
 X      DB  0FFH,0FFH
 dv    real8 3.4
.CODE
 main PROC
add r10d,11223344h
 add  rdx,11223344h
 add  edx,11223344h
 add dword ptr [rdx],11223344h

 add  eax,[ebx]
 add  eax,[rbx]
 add  ax,[rbx]
 add  ax,[ebx]
 add  al,[rbx]
 add  rax,[rbx]
 add  rax,[ebx]

 add  eax,[r9d]
 add  eax,[r9]
 add  rax,r14
 add  r14, rax
mov  r9,1122334455667788h 
add  rdx,11223344h
add  qword ptr [rdx],11223344h
add  dword ptr [rdx],11223344h

add  r10,11223344h
add  dword ptr [r10],11223344h
add  r8d, 11223344h
add  r8w, 1122h
add  r8b, 11h
push rax
push rdx
call  func1
 
 
 movzx rax,x
 movsx rax,x+1
 mov  mmword ptr x,rax
 mov  mmword ptr x+8,rdx
; cmpxchg16b x
 mov rcx,100000001h

 push rax
 shl rax,4
 mov  al,7
 add  ah,13h
 shl  ax, 2
 mov  bx,2
 mul  bl
 imul  bx,2
 xchg  eax,ebx

l1:
 mov  rax,0F0000000H
 add  rax,90000000H
 mov  Al,X
 mov  BL,X[1]
 MOV  RAX,1234567887654321H
 LEA  EAX,X
 MOV  CL,[EAX]

 LEA  RAX,X
 MOV  SIL, [RAX]

 ; MOV  Cl,X[RAX]
; MOV  DL,X[RAX+RBX*4]
; MOV  CL,[RAX+1234567801H]
   LEA  RAX, X
   MOV  CL,[RAX]


              ; eax=0; for (ebx=1;ebx<=100;ebx++) eax=eax+ebx;
   mov  rdx, 0
   mov  rbx, 1
lp: cmp  rbx, 100
   jg   exit
   add  rdx, rbx
   add  rbx, 1
   jmp  lp
exit:
   mov   rcx, offset lpFmt

   call printf
;   invoke printf,offset lpFmt,eax
  mov rdx, 0
  call ExitProcess
  ; invoke ExitProcess, 0
main endp

func1 proc
   mov  rbx,[rsp+8]
   mov  rcx,[rsp+16]
   add  rbx, rcx
   ret
func1 endp
end