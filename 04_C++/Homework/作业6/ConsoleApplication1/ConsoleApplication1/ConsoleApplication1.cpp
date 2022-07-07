#include <stdio.h> 
struct A {
	A() { printf("别理我"); }
	A(const char* s) { printf("%s",s); }
} a("烦着呢");
A f() { printf("一边去");  return a; }
int fun() { printf("shit"); return 1; }
void main(void) { A f(); int fun(); }

//#include <iostream>
//using namespace std;
//struct A { A() { cout <<'A'; } };
//struct B { B() { cout << 'B'; } };
//struct C : A { C() { cout << 'C'; } };
//struct D : B, virtual C { D() { cout << 'D'; } };
//struct E : A, virtual D {
//	D  d;
//	E() : A() { cout << 'E'; }
//};
//struct F : B, virtual C, E, virtual D {
//	D  d;
//	F(){ cout << 'F'; }
//};
//void main() {
//	A  a;  cout << "\n";	//输出= 
//	B  b;  cout << "\n";	//输出= 
//	C  c;  cout << "\n";	//输出= 
//	D  d;  cout << "\n";	//输出= 
//	E  e;  cout << "\n";	//输出= 
//	F  f;  cout << "\n";	//输出= 
//}

//int  x = 3;	//学号最后一位十进制数
//int  y = x + 3;
//struct A {
//	int  x;
//	static  int& y;
//public:
//	operator int() const { return x + y; }
//	int& v(int& x) {
//		for (int y = 1; x < 301; x ^= y++) {
//			if (x > 300) {
//				x -= 31; y -= 2;
//			}
//			return ++x;
//		}
//	}
//		A& operator++() { ++x;  ++y;  return *this; }
//		A(int x = A::y + 2, int y = ::x + A::y) { A::x = x + 1;  A::y = y + 2; }
//	};
//	int& A::y = ::y;
//	void main() {
//		A  a(3, 4), b(a), c;
//		int  i, & j = i;
//		int  A::* p = &A::x;
//		j = a.x;			// i = 
//		cout << i << endl;
//		i = a.y;			// i = 
//		cout << i << endl;
//		i = a.*p;		// i = 
//		cout << i << endl;
//		i = ++a;		// i = 
//		cout << i << endl;
//		i = b.y + ::y;		// i = 
//		cout << i << endl;
//		(b.v(i) = 3) += 2;	// i = 
//		cout << i << endl;
//	}

//class PER{
//	const  int  n;		//存放自然数
//	int* const  f;		//存放所有有效因子, 所有因子之和等于 n 才是完美数
//	int c;			//有效因子个数 ：正数表示是完美数 ，负数表示不是
//public:
//	PER(int p);				//用自然数 p 初始化 n, f, c
//	PER(const  PER& p);			//深拷贝构造函数
//	PER& operator=(const PER& p);	//深拷贝赋值运算
//	operator int() const;			//若不是完全数则返回 0，否则返回 c
//	int operator [] (int k) const;		//返回 k 所指示的因子, 若 k < 0 或 k >= c 返回 0
//	~PER();				//析构函数
//};
//PER::PER(int p):n(p),f()			//用自然数 p 初始化 n, f, c
//{
//	int *temp=new int[p],num=0,sum=0;
//	for (int i = 1; i < p; i++)
//	{
//		if (p % i == 0)
//			temp[num++] = i;
//	}
//	*(const_cast<int**>(&f))= new int[num];
//	for (int i = 0; i < num; i++)
//	{
//		f[i] = temp[i];
//		sum += f[i];
//	}
//	if (sum == n)c = num;
//	else c = -1 * num;
//}
//PER::PER(const  PER& p):n(p.n),f()		//深拷贝构造函数
//{
//	*(const_cast<int**>(&f)) = new int[p.n];
//	for (int i = 0; i < p.n; i++)
//		f[i] = p.f[i];
//	c = p.c;
//}
//PER& PER::operator=(const  PER& p)	//深拷贝赋值运算
//{
//	if (f)
//		delete[]f;
//	*(const_cast<int**>(&f)) = new int[p.n];
//	for (int i = 0; i < p.n; i++)
//		f[i] = p.f[i];
//	c = p.c;
//	return *this;
//}
//PER::operator int() const			//若不是完全数则返回 0，否则返回 c
//{
//	if (c < 0)return 0;
//	else return c;
//}
//int PER::operator [ ] (int k) const		//返回 k 所指示的因子, 若 k < 0 或 k >= c 返回 0
//{
//	if (k < 0 || k >= c)return 0;
//	else return f[k];
//}
//PER::~PER()			//析构函数
//{
//	delete[]f;
//}
//int main(void)
//{
//	PER A(27);
//	cout << (int)A << endl;
//	return 0;
//}