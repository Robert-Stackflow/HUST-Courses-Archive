.686P
.model flat,c
 option casemap:none    ; ���������� ��Сд���У������ windows.inc ������д�   
 include windows.inc 
 SetUnhandledExceptionFilter PROTO STDCALL :DWORD
 MessageBoxA PROTO STDCALL :DWORD,:DWORD, :DWORD,:DWORD
 ExitProcess PROTO STDCALL :DWORD
 sprintf  PROTO  :VARARG
 includelib      msvcrt.lib


.data
  szMsg  db   "exception occur at %08x, code: %08x, flag :%08x",0
  szTitle    DB   "�쳣�Ѵ���",0
  szContent  db  "����������",0
  szNotOccur db  "����Ϣ������ʾ",0
;  DATAX  DD  10,20    ; ΪBOUND ָ��������
  lpOldHandle  dd  ?

.code


MyExceptionProcess  proc  lpExceptionPoint
    local szBuf[256]:byte
	pushad
	mov  esi, lpExceptionPoint
	mov  edi, (EXCEPTION_POINTERS ptr [esi]).ContextRecord
	mov  esi, (EXCEPTION_POINTERS ptr [esi]).pExceptionRecord
	invoke sprintf, addr szBuf, addr szMsg, [edi].CONTEXT.regEip, 
	               [esi].EXCEPTION_RECORD.ExceptionCode, 
		           [esi].EXCEPTION_RECORD.ExceptionFlags
	invoke MessageBoxA, NULL,addr szBuf,NULL, MB_OK
	mov   [edi].CONTEXT.regEip,  offset SafePlace
	popad
	mov  eax,EXCEPTION_CONTINUE_EXECUTION
	ret
MyExceptionProcess  endp

start:   
    invoke SetUnhandledExceptionFilter, addr  MyExceptionProcess
	mov  lpOldHandle,  eax

	xor  eax,eax
    mov  dword ptr [eax], 0   ; �����쳣����䣬�Ƿ�����
	 ; �����MessageBoxA ��������ִ��
     ; ���쳣����������޸���EIP��ʹָ֮����SafePlace

    invoke MessageBoxA,NULL,addr szNotOccur, addr szTitle,MB_OK

;	mov  ax,7fffh
;	add  ax,3
;	mov  ebx,110
;	INT 3
;	INTO
;BOUND  ebx,DATAX
;	
;   INT  5
          ; �쳣����󣬴�SafePlace����ʼִ�� 
SafePlace:
    invoke MessageBoxA,NULL,addr szContent, addr szTitle,MB_OK
    invoke SetUnhandledExceptionFilter, lpOldHandle
    invoke ExitProcess, 0


end start