.data
  ;  extern MessageBoxA : proc   ; ��ȷ
  ;  extrn MessageBoxA : proc   ; ��ȷ
  ;  MessageBoxA PROTO STDCALL   ; ��ȷ
  MessageBoxA proto :DWORD ,:DWORD
  extrn ExitProcess : proc 
  lpContent db  'Hello x86-64',0
  lpTitle   db  'My first x86-64 Application',0
.code
start proc
   sub  rsp, 28h
   xor  r9d, r9d
   lea  r8,  lpTitle
   lea  rdx, lpContent
   xor  rcx,rcx
   call MessageBoxA
   add  rsp,28h
   ; ���� ret ָ��Ҳ����
   ; ret
   mov  rcx,0
   call ExitProcess
start endp
end