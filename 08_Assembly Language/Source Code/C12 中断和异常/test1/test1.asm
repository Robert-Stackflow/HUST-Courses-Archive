.386
.model flat,STDCALL
 OPTION CASEMAP:NONE    ; 必须先申明 大小写敏感，否则对 windows.inc 处理会有错   
 include windows.inc 
 SetUnhandledExceptionFilter PROTO STDCALL :DWORD
 MessageBoxA PROTO STDCALL :DWORD,:DWORD, :DWORD,:DWORD
 ExitProcess PROTO STDCALL :DWORD
 sprintf  PROTO c :VARARG
 includelib      msvcrt.lib
.data
  szMsg  db   "exception occur at %08x, code: %08x, flag :%08x",0
  szTitle    DB   "异常已处理",0
  szContent  db  '运行正常了',0
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
	mov   [edi].CONTEXT.regEip, offset SafePlace
	popad
	mov  eax,EXCEPTION_CONTINUE_EXECUTION
	ret
MyExceptionProcess  endp

 start:  
    invoke SetUnhandledExceptionFilter, addr  MyExceptionProcess
	mov  lpOldHandle,  eax
	xor  eax,eax
	mov  dword ptr [eax], 0

SafePlace:
    invoke MessageBoxA,NULL,addr szContent, addr szTitle,MB_OK
    invoke SetUnhandledExceptionFilter, lpOldHandle
    invoke ExitProcess, 0
END start