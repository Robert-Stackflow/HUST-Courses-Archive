#include <windows.h>
#include <stdio.h>
int modify_var = 0;

EXCEPTION_DISPOSITION  __cdecl _except_handler(
struct _EXCEPTION_RECORD *ExceptionRecord,
	void   * EstablisherFrame,
struct _CONTEXT *ContextRecord,
	void   * DispatcherContext)
{
//	ContextRecord->Eax = (DWORD)&modify_var;
	printf(" enter exception processing ...\n");
	//return ExceptionContinueExecution;
		return ExceptionContinueSearch;
	//该值会导致引起异常的语句 "mov[eax],1"重新执行，即修改modify_var
}

long __stdcall  MyExceptionProcess(EXCEPTION_POINTERS * excp)
{
	printf("Error   address :  %08x \n", excp->ExceptionRecord->ExceptionAddress);
	printf("CPU   register:\n");
	printf("eax = %08x \n", excp->ContextRecord->Eax);
//	return   EXCEPTION_EXECUTE_HANDLER;
	excp->ContextRecord->Eax = (DWORD)&modify_var;
	return EXCEPTION_CONTINUE_EXECUTION;
}

int main()
{ 
	SetUnhandledExceptionFilter(MyExceptionProcess);

	DWORD handler = (DWORD)_except_handler;
	__asm
	{   push handler   // handler函数的地址
		push FS : [0]  // 原 EXECEPTION_REGISTRATION_RECORD 的头指针
		mov FS : [0], ESP // FS:[0] 保存新的 EXECEPTION_REGISTRATION_RECODE头指针
	}
	printf("before modification:  %d\n", modify_var);
	__asm
	{   mov eax, 0
		mov[eax], 1 // 此处会引发一个异常，访问地址非法
	}
	printf("After  modification:  %d\n", modify_var);
	__asm
	{	// 移除 新加的 EXECEPTION_REGISTRATION_RECORD 节点，恢复原异常处理
		mov eax, [ESP]
			mov FS : [0], EAX
			add esp, 8
	}
	return 0;
}
