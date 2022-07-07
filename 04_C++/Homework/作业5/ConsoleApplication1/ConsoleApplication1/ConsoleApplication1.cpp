#include<iostream>
int   x = 3, y = x + 3;
struct A {
	int  x;
	static int& y;
public:
	operator int() const { return x + y; }
	int& v(int& x) {
		for (int y = 1; x < 201; x ^= y, y++)
			if (x > 200) { x -= 31; y -= 2; }
		return ++x;
	}
	A& operator++() { ++x; ++y; return *this; }
	A(int x = ::x + 2, int y = ::y + 3) { A::x = x;  A::y = y; }
};
int& A::y = ::x;
int main() {
	A  a(2,3), b(a), c;
	std::cout << a.y << std::endl;
	int  i, & j = i, A::* p = &A::x;
	i = a.y;
	std::cout << i << std::endl;
	j = a.x++; 			//i=
	std::cout << i << std::endl;
	i = a.*p;			//i=
	std::cout << i << std::endl;
	i = ++a; 			//i=
	std::cout << i << std::endl;
	i = b.y + ::y;			//i=
	std::cout << i << std::endl;
	(b.v(i) = 2) += 3;	//i=
	std::cout << i << std::endl;
	return 0;
}