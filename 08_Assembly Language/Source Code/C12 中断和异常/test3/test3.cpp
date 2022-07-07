// test3.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
 #include <Windows.h>
//#define EXCEPTION_EXECUTE_HANDLER      1
#include <stdio.h>

int main() {

	int  x = 10;
	int  y = 0;
	int  result;

	__try {
	    result = x / y;
		printf("This message will not occur .....\n");
    }
	__except (EXCEPTION_EXECUTE_HANDLER){
		printf("exception is processing  .... over \n");
	}
	printf("program  continue ..... hello \n");

	return 0;
}