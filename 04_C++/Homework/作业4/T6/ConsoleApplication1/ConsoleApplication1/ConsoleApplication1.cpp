#include<iostream>
using namespace std;
class A {
	int a;
	static friend int f();
	friend int g();
public:
	friend int A();
	A(int x) : a(x) { };
} a(5);
int f() { return a.a; }
int g() { return a.a; }
int main(void)
{
	return 0;
}