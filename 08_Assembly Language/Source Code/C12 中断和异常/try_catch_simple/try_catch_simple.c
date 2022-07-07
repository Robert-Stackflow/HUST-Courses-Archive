#define EXCEPTION_EXECUTE_HANDLER      1
#define EXCEPTION_CONTINUE_SEARCH      0
#define EXCEPTION_CONTINUE_EXECUTION (-1)
//C:\Program Files(x86)\Microsoft Visual Studio\2019\Community\VC\Tools\MSVC\14.22.27905\include\excpt.h
#include <stdio.h>

int main() {

	int  x = 10;
	int  y = 0;
	int  result;

	__try {
		printf("enter try block .....\n");
		result = x / y;
		printf("This message will not occur .....\n");
	}
	__except (EXCEPTION_EXECUTE_HANDLER) 
	//__except (EXCEPTION_CONTINUE_SEARCH) { }
	{
		printf("exception is processing  .... over \n");
	}
	printf("program  continue ..... hello \n");

	return 0;
}