// c_swap.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
using namespace std;
int main()
{
	int  a = 20, b = 30;
	cout << "a=" << a << "  b=" << b << endl;
	a = (a + b) - (b = a);
	cout << "a=" << a << "  b=" << b << endl;
    std::cout << "Hello World!\n";
}
