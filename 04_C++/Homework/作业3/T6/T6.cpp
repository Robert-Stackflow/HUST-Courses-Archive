#include<iostream>
using namespace std;
struct A { A() { cout << 'A'; } };
struct B { B() { cout << 'B'; } };
struct C : A { C() { cout << 'C'; } };
struct D : A, virtual B { D() { cout << 'D'; } };
struct E : A, virtual B, virtual C {
	D d;
	E() { cout << 'E'; }
};
struct F : A, virtual B, virtual C, D, E {
	C  c;
	E  e;
	F() { cout << 'F'; }
};
int main(void)
{
	A  a;
	printf("\n");
	B  b;
	printf("\n");
	C  c;
	printf("\n");
	D  d;
	printf("\n");
	E  e;
	printf("\n");
	F  f;
	printf("\n");
	system("pause");
	return 0;
}