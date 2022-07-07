// test4.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>

#include <stdio.h>

int main() {
	LPEXCEPTION_POINTERS p_exinfo;
	_EXCEPTION_POINTERS  *excp;
	int  x = 10;
	int  y = 0;
	int  result;

	__try {
		result = x / y;
		printf("This message will not occur .....\n");
	}
	//excp = GetExceptionInformation();   // 错误,该语句只能用在except后的表达式内
	 __except (EXCEPTION_EXECUTE_HANDLER){   // 采用该形式正确
	     //  __except (UnhandledExceptionFilter(GetExceptionInformation()))  // 有问题，系统弹出了错误
	//  __except (p_exinfo = GetExceptionInformation()){  //错误用法
		printf("exception is processing  .... over \n");
	}
	printf("program  continue ..... hello \n");

	return 0;
}