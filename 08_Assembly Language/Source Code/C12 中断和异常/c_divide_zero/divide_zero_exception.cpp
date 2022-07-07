/*
* 除零操作
* divide 函数当除数为零时抛出一个 char* 类型异常
* 为了测试 catch(...) 的功能使用 throw 1; 抛出了一个 int 类型的异常
*/
#include <stdio.h>

double divide(const double& dividend, const double& divisor) {
	if (divisor == 0) {
		throw "除数为 0！";
	}
	return dividend / divisor;
}

int main() {

	double num1 = 10, num2 = 0;
	double result = -1;
	try {
		result = divide(num1, num2);
	//	throw 1;
	}
	// 捕获相应类型的异常
	catch (const char* msg) {
		printf("%s\n", msg);
	}
	// 能处理任何类型的异常
	catch (...) {
		printf("error\n");
	}
	printf("%.2f\n", result);

	return 0;

}