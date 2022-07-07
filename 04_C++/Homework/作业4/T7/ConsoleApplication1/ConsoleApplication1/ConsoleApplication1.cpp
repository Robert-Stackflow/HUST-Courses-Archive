#include<iostream>
using namespace std;
class STACK {
	const int max; 		//栈能存放的最大元素个数 
	int  top; 			//栈顶元素位置 
	char* stk;
public:
	STACK(int max);
	~STACK();
	int push(char v); 	//将v压栈，成功时返回1，否则返回0 
	int pop(char& v); 	//弹出栈顶元素，成功时返回1，否则返回0 
};
class REVERSE : STACK {
public:
	REVERSE(char* str); //将字符串的每个字符压栈 
	~REVERSE(); 	 //按逆序打印字符串
};
STACK::STACK(int max):max((stk = new char[max]) ? max : 0),top(-1)
{
}
STACK::~STACK()
{
	char ch;
	for (int i = 0; i < max; i++)
		pop(ch);
	delete stk;
	*(const_cast<int*>(&max)) = 0;
	top = 0;
}
int STACK::push(char v)
{
	if (top==max) return 0;
	else
	{
		stk[++top] = v;
		return 1;
	}
}
int STACK::pop(char& v)
{
	if (top==-1) return 0;
	else
	{
		v = stk[top--];
		printf("%c", v);
		return 1;
	}
}
REVERSE::REVERSE(char* str):STACK(strlen(str))
{
	int len = strlen(str);
	for (int i = 0; i < len; i++)
	{
		push(str[i]);
	}
}
REVERSE::~REVERSE()
{
}

int  main(void) {
	char s[8] = "abcdefg";
	REVERSE a(s);
	return 0;
}