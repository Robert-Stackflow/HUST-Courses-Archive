/*
* �������
* divide ����������Ϊ��ʱ�׳�һ�� char* �����쳣
* Ϊ�˲��� catch(...) �Ĺ���ʹ�� throw 1; �׳���һ�� int ���͵��쳣
*/
#include <stdio.h>
#include <exception>
#include <iostream>
using namespace std;

double divide(const double& dividend, const double& divisor) {
//	if (divisor == 0) {
//		throw "����Ϊ 0��";
//	}
	return dividend / divisor;
}

int main() {

	double num1 = 10, num2 = 0;
	double result = -1;
	try {
	//	result = divide(num1, num2);
		result = num1 / num2;
		throw 1;
	}	catch (int & value)
	/*
	// ������Ӧ���͵��쳣
	catch (const char* msg) {
		printf("%s\n", msg);
	}
	// �ܴ����κ����͵��쳣
	catch (...) {
		printf("error\n");
	}
	printf("%.2f\n", result);
	*/
	
	{
		cout << "�� 0 �쳣" << endl;
	}

	return 0;

}