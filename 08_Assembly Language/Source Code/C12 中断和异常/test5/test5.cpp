// test5.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "stdio.h"
#include "windows.h"
#include <winternl.h>

int exception_filter(LPEXCEPTION_POINTERS p_exinfo)
{
	printf("Error address %x \n", p_exinfo->ExceptionRecord->ExceptionAddress);
	printf("Error Code %08x \n", p_exinfo->ExceptionRecord->ExceptionCode);
	printf("CPU register: \n");
	printf("eax= %08x ebx=%08x  ecx=%08x  edx=%08x \n", p_exinfo->ContextRecord->Eax,
		p_exinfo->ContextRecord->Ebx, p_exinfo->ContextRecord->Ecx,
		p_exinfo->ContextRecord->Edx);
	if (p_exinfo->ExceptionRecord->ExceptionCode == EXCEPTION_ACCESS_VIOLATION)
	{
		puts("存储保护异常");
	}
	if (p_exinfo->ExceptionRecord->ExceptionCode == EXCEPTION_INT_DIVIDE_BY_ZERO)
	{
		puts("被0除异常");
	}
	return 1;
}

void main()
{
	int  x = 10;
	int  y = 0;
	int  result=3;
	int  select;
	TEB  *p;
	puts("hello");
	scanf_s("%d", &select);
	__try
	{
			if (select == 1) {
			  int* p;
			  p = 0;
			  *p = 45;	// 该语句会导致一个异常  EXCEPTION_ACCESS_VIOLATION
			  puts("This Message will not occur ...ACCESS_VIOLATION ");
			}
			if (select==2) {
				result = x / y;  // 该语句会导致一个异常  EXCEPTION_INT_DIVIDE_BY_ZERO
				puts("This Message will not occur ...INT_DIVIDE_BY_ZERO ");
			}
			if (select != 1 && select != 2) {
				puts("no exception occur");
			}
		}
	__except (exception_filter(GetExceptionInformation()))
	   {
			puts("异常已处理");
		}
	puts("world");
	result = x / y;  // 该语句会导致一个异常  EXCEPTION_INT_DIVIDE_BY_ZERO

	getchar();
}


