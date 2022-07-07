// test2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>

#include <stdio.h>

// EXCEPTION_EXECUTE_HANDLER equ 1   //  表示我已经处理了异常, 可以优雅地结束了 
// EXCEPTION_CONTINUE_SEARCH equ 0   //  表示我不处理, 其他人来吧, 于是windows调用默认的处理程序显示一个错误框, 并结束 
// EXCEPTION_CONTINUE_EXECUTION equ  - 1 // 表示错误已经被修复, 请从异常发生处继续执行 


long __stdcall callback(_EXCEPTION_POINTERS* excp)
{
	printf("Error address %x \n", excp->ExceptionRecord->ExceptionAddress);
	printf("Error Code %08x \n", excp->ExceptionRecord->ExceptionCode);
    printf("CPU register: \n");
	printf("eax= %08x ebx=%08x  ecx=%08x  edx=%08x \n", excp->ContextRecord->Eax,
		excp->ContextRecord->Ebx, excp->ContextRecord->Ecx,
		excp->ContextRecord->Edx);
	excp->ContextRecord->Eip += 3;
	    // 这里有问题： 我是知道 除法指令占了三个字节
	    // 若不知道有多少个字节，如何让程序继续执行 ？
//	return  EXCEPTION_EXECUTE_HANDLER;
	return  EXCEPTION_CONTINUE_EXECUTION;
}


int main() {

	int  x = 10;
	int  y = 0;
	int  result;
	// 如果将下面的行注释掉，程序崩溃
	SetUnhandledExceptionFilter(callback);
	
	result = x / y;

	printf("program  continue ..... hello \n");


	return 0;

}