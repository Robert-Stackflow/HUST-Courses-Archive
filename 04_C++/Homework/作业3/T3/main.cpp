#include<iostream>
using namespace std;
struct A {
	int a = 0;
	int x = 1;
	void f() { cout << "A::f()"; }
	virtual void g() { cout << "A::g()"; }
	A(int x) { }
};
struct B: A {
	int x = 11;
	int y = 12;
	virtual void f() { cout << "B::f()"; }
	void g() { cout << "B::g()"; }
	void h() { cout << "B::h()"; }
	B(int x): A(x) { }
};
struct C: B {
	int x = 21;
	int y = 22;
	int z = 23;
	void f() { cout << "C::f()"; }
	void g() { cout << "C::g()"; }
	virtual void h() { cout << "C::h()"; }
	C(int x): B(x) { }
} c(1);
int main() {
	A *p = &c;
	p->f();
	p->g();
	// p->h();
	cout << p->a<<endl;
    cout << p->x << endl;
    // cout << p->y<<endl;
    // cout << p->z<<endl;
    /**/
    B *q = &c;
	q->f();
	q->g();
	q->h();
    cout << p->a << endl;
    cout << q->x << endl;
    cout << q->y << endl;
    // cout << q->z<<endl;
}
