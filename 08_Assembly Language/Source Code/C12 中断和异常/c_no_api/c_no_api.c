#include <windows.h>
#include <stdio.h>
int modify_var=0;

EXCEPTION_DISPOSITION  __cdecl _except_handler(
       struct _EXCEPTION_RECORD *ExceptionRecord,
	   void   * EstablisherFrame,
       struct _CONTEXT *ContextRecord,
	   void   * DispatcherContext)
{
	ContextRecord->Eax = (DWORD)&modify_var;
//	printf(" enter exception processing ...\n");
	return ExceptionContinueExecution;
//	return ExceptionContinueSearch;
	//��ֵ�ᵼ�������쳣����� "mov[eax],1"����ִ�У����޸�modify_var
}


int main()
{   
	DWORD handler = (DWORD)_except_handler;
	__asm
	{   
		push handler   // handler�����ĵ�ַ
		push FS : [0]  // ԭ EXECEPTION_REGISTRATION_RECORD ��ͷָ��
		mov FS : [0], ESP // FS:[0] �����µ� EXECEPTION_REGISTRATION_RECODEͷָ��
	}
	printf("before modification:  %d\n", modify_var);
	__asm
	{   mov eax, 0  
		mov[eax], 1 // �˴�������һ���쳣�����ʵ�ַ�Ƿ�
	}
	printf("After  modification:  %d\n", modify_var);
	__asm
	{	// �Ƴ� �¼ӵ� EXECEPTION_REGISTRATION_RECORD �ڵ㣬�ָ�ԭ�쳣����
		mov eax, [ESP]    
		mov FS : [0], EAX  
		add esp, 8       
	}
	return 0;
}
