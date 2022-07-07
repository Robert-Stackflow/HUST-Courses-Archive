#include<iostream>
using namespace std;
class A {
	int a1;
protected:
	int a2;
public:
	int a3;
	~A() { };
};
class B : protected A {
	int b1;
protected:
	int b2;
public:
	//A::a1;
	A::a2;
	int b3;
	~B() { };
};
struct C : private B {
	int c1;
protected:
	int c2;
	B::A::a2;
	A::a3;
public:
	using B::b2;
	int c3;
	int a3;
	~C() { };
};
int main() {
	C c;
	cout << c.b2;
	//cout << c.B::b2;
}