; 程序在运行的过程中，自我修改
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
;  WinMainCRTStartup proc  ; 子系统选择 Windows
  mainCRTStartup proc
;main  proc
    sub  rsp, 28H
	lea  r9,  oldprotect   ; 对应参数 ：pfloldProtect 指向前一个内存保护值
	mov  r8d, 40H          ; 对应参数 ：flNewProtect  要应用的内存保护的类型
	mov  rdx, 1            ; 对应参数 ：dwsize,要更改的内存页面区域的大小
	lea  rcx, ModifyHere   ; 对应参数 ：lpAddress ，要更改保护特性的虚拟内存的基址
	call VirtualProtect
	add  rsp, 28H

    lea  rax, ModifyHere
;	inc  byte ptr [rax]   ; jz,jnz的机器码分别 为 74H，75H
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