#include "MAT.h"
template MAT<int>;
template MAT<long long>;
template MAT<float>;
template MAT<double>;
extern const char* TestMAT(int& s); //用于实验四
int main(int argc, char* argv[])	//请扩展main()测试其他运算
{
	cout << "----------------------------------------------------" << endl;
	cout << "0.TestMAT   1.int   2.long long   3.float   4.double" << endl;
	cout << "----------------------------------------------------" << endl;
	cout << "Please Input Your Choice:";
	int choice;
	cin >> choice;
	if (choice == 0)
	{
		int s;
		const char* e = TestMAT(s);
		cout << "Score:" << s << "\nResult:" << e << endl;
	}
	else if (choice == 1)
	{
		MAT<int> a(1, 2), b(2, 2), c(1, 2);
		char t[2048];
		a[0][0] = 1; //类似地初始化矩阵的所有元素
		a[0][1] = 2; //等价于“*(a.operator[ ](0)+1)=2;”即等价于“*(a[0]+1)=2;”
		a.print(t);	 //初始化矩阵后输出该矩阵
		cout << t << "--------------------------" << endl;
		b[0][0] = 3;
		b[0][1] = 4; //调用T* const operator[ ](int r)初始化数组元素
		b[1][0] = 5;
		b[1][1] = 6;
		b.print(t);
		cout << t << "--------------------------" << endl;
		c = a * b; //测试矩阵乘法运算
		c.print(t);
		cout << t << "--------------------------" << endl;
		(a + c).print(t); //测试矩阵加法运算
		cout << t << "--------------------------" << endl;
		c = c - a; //测试矩阵减法运算
		c.print(t);
		cout << t << "--------------------------" << endl;
		c += a; //测试矩阵“+=”运算
		c.print(t);
		cout << t << "--------------------------" << endl;
		c = ~a; //测试矩阵转置运算
		c.print(t);
		cout << t << "--------------------------" << endl;
	}
	else if (choice == 2)
	{
		MAT<long long> a(1, 2), b(2, 2), c(1, 2);
		char t[2048];
		a[0][0] = 1ll; //类似地初始化矩阵的所有元素
		a[0][1] = 2ll; //等价于“*(a.operator[ ](0)+1)=2;”即等价于“*(a[0]+1)=2;”
		a.print(t);	   //初始化矩阵后输出该矩阵
		cout << t << "--------------------------" << endl;
		b[0][0] = 3ll;
		b[0][1] = 4ll; //调用T* const operator[ ](int r)初始化数组元素
		b[1][0] = 5ll;
		b[1][1] = 6ll;
		b.print(t);
		cout << t << "--------------------------" << endl;
		c = a * b; //测试矩阵乘法运算
		c.print(t);
		cout << t << "--------------------------" << endl;
		(a + c).print(t); //测试矩阵加法运算
		cout << t << "--------------------------" << endl;
		c = c - a; //测试矩阵减法运算
		c.print(t);
		cout << t << "--------------------------" << endl;
		c += a; //测试矩阵“+=”运算
		c.print(t);
		cout << t << "--------------------------" << endl;
		c = ~a; //测试矩阵转置运算
		c.print(t);
		cout << t << "--------------------------" << endl;
	}
	else if (choice == 3)
	{
		MAT<float> a(1, 2), b(2, 2), c(1, 2);
		char t[2048];
		a[0][0] = 1.1f; //类似地初始化矩阵的所有元素
		a[0][1] = 2.2f; //等价于“*(a.operator[ ](0)+1)=2;”即等价于“*(a[0]+1)=2;”
		a.print(t);		//初始化矩阵后输出该矩阵
		cout << t << "--------------------------" << endl;
		b[0][0] = 3.3f;
		b[0][1] = 4.4f; //调用T* const operator[ ](int r)初始化数组元素
		b[1][0] = 5.5f;
		b[1][1] = 6.6f;
		b.print(t);
		cout << t << "--------------------------" << endl;
		c = a * b; //测试矩阵乘法运算
		c.print(t);
		cout << t << "--------------------------" << endl;
		(a + c).print(t); //测试矩阵加法运算
		cout << t << "--------------------------" << endl;
		c = c - a; //测试矩阵减法运算
		c.print(t);
		cout << t << "--------------------------" << endl;
		c += a; //测试矩阵“+=”运算
		c.print(t);
		cout << t << "--------------------------" << endl;
		c = ~a; //测试矩阵转置运算
		c.print(t);
		cout << t << "--------------------------" << endl;
	}
	else if (choice == 4)
	{
		MAT<double> a(1, 2), b(2, 2), c(1, 2);
		char t[2048];
		a[0][0] = 1.1; //类似地初始化矩阵的所有元素
		a[0][1] = 2.2; //等价于“*(a.operator[ ](0)+1)=2;”即等价于“*(a[0]+1)=2;”
		a.print(t);	   //初始化矩阵后输出该矩阵
		cout << t << "--------------------------" << endl;
		b[0][0] = 3.3;
		b[0][1] = 4.4; //调用T* const operator[ ](int r)初始化数组元素
		b[1][0] = 5.5;
		b[1][1] = 6.6;
		b.print(t);
		cout << t << "--------------------------" << endl;
		c = a * b; //测试矩阵乘法运算
		c.print(t);
		cout << t << "--------------------------" << endl;
		(a + c).print(t); //测试矩阵加法运算
		cout << t << "--------------------------" << endl;
		c = c - a; //测试矩阵减法运算
		c.print(t);
		cout << t << "--------------------------" << endl;
		c += a; //测试矩阵“+=”运算
		c.print(t);
		cout << t << "--------------------------" << endl;
		c = ~a; //测试矩阵转置运算
		c.print(t);
		cout << t << "--------------------------" << endl;
	}
	system("pause");
	return 0;
}