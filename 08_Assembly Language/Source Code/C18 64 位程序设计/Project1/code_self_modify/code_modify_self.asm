; ���������еĹ����У������޸�
 extern MessageBoxA : proc
 extern ExitProcess : proc
 extern VirtualProtect : proc
;    includelib  libcmt.lib
;	  includelib libvcruntime.lib
; includelib libucrt.lib
;  includelib     legacy_stdio_definitions.lib
.data
 szMsg1   db 'before Modify : Hello ',0
 szMsg2   db 'After  Modify : Interesting ',0
 szTitle  db 'Modify Program Self',0
 oldprotect   dd ?

.code
;  WinMainCRTStartup proc  ; ��ϵͳѡ�� Windows
  mainCRTStartup proc
;main  proc
    sub  rsp, 28H
	lea  r9,  oldprotect   ; ��Ӧ���� ��pfloldProtect ָ��ǰһ���ڴ汣��ֵ
	mov  r8d, 40H          ; ��Ӧ���� ��flNewProtect  ҪӦ�õ��ڴ汣��������
	mov  rdx, 1            ; ��Ӧ���� ��dwsize,Ҫ���ĵ��ڴ�ҳ������Ĵ�С
	lea  rcx, ModifyHere   ; ��Ӧ���� ��lpAddress ��Ҫ���ı������Ե������ڴ�Ļ�ַ
	call VirtualProtect
	add  rsp, 28H

    lea  rax, ModifyHere
;	inc  byte ptr [rax]   ; jz,jnz�Ļ�����ֱ� Ϊ 74H��75H
	lea  rdx, szMsg1
	xor  eax, eax
ModifyHere:
    jz   next
	lea  rdx, szMsg2
next:
    sub  rsp, 28H
	mov  r9d, 0
	lea  r8,  szTitle
	mov  rcx, 0
	call MessageBoxA
	add  rsp, 28h
	mov  rcx, 0
    call ExitProcess
;WinMainCRTStartup endp
;main endp
mainCRTStartup endp
end