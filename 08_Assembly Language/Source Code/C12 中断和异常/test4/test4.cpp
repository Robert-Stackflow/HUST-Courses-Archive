// test4.cpp : �������̨Ӧ�ó������ڵ㡣
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
	//excp = GetExceptionInformation();   // ����,�����ֻ������except��ı��ʽ��
	 __except (EXCEPTION_EXECUTE_HANDLER){   // ���ø���ʽ��ȷ
	     //  __except (UnhandledExceptionFilter(GetExceptionInformation()))  // �����⣬ϵͳ�����˴���
	//  __except (p_exinfo = GetExceptionInformation()){  //�����÷�
		printf("exception is processing  .... over \n");
	}
	printf("program  continue ..... hello \n");

	return 0;
}