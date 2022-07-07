#include<iostream>
using namespace std;
struct A {
	//static int x = 1;
	static const int y = 2;
	static const volatile int z = 3;
	//static volatile int w = 4;
	static const float u;
};
//static int A::x = 11;
const int A::y = 22;
int volatile A::z = 33;
//int volatile A::w = 44;
const float A::u = 55.0f;
int main(void)
{
	return 0;
}