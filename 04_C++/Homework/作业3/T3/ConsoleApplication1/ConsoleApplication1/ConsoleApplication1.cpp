#include<iostream>
using namespace std;
//struct A {
//	int a = 0;
//	int x = 1;
//	void f() { cout << "A::f()"; }
//	virtual void g() { cout << "A::g()"; }
//	A(int x) { }
//};
//struct B : A {
//	int x = 11;
//	int y = 12;
//	virtual void f() { cout << "B::f()"; }
//	void g() { cout << "B::g()"; }
//	void h() { cout << "B::h()"; }
//	B(int x) : A(x) { }
//};
//struct C : B {
//	int x = 21;
//	int y = 22;
//	int z = 23;
//	void f() { cout << "C::f()"; }
//	void g() { cout << "C::g()"; }
//	virtual void h() { cout << "C::h()"; }
//	C(int x) : B(x) { }
//} c(1);
class A {
	int x;
	virtual int f() { return 0; }
	virtual int g() = 0;
protected:
	int  y;
public:
	A() { }
};
struct B : A {
	//A::x;
	using A::y;
	//long f() { return 1L; };
	int g1(int) { return 1; }
} b;
//A* p = new A;
B* q = new B;
int f(A, B);
A g(B&);
int h(B*);

int main() {
	//A* p = &c;
	//p->f();
	//cout << endl;
	//p->g();
	//cout << endl;
	////p->h();
	//cout << p->a << endl;
	//cout << p->x << endl;
	////cout << p->y;
	////cout << p->z;
	///**/
	//B* q = &c;
	//q->f();
	//cout << endl;
	//q->g();
	//cout << endl;
	//q->h();
	//cout << endl;
	//cout << p->a<<endl;
	//cout << q->x << endl;
	//cout << q->y << endl;
	//cout << q->z;
}