#include "Stack.h"
STACK::STACK(int m) : QUEUE(m), q(QUEUE(m)) {}										//初始化栈：最多存放2m-2个元素
STACK::STACK(const STACK& s) : QUEUE(s), q(QUEUE(s.q)) {}							//用栈s深拷贝初始化栈
STACK::STACK(STACK&& s) noexcept : QUEUE((QUEUE&&)s), q(QUEUE((QUEUE&&)s.q)) {} //用栈s移动拷贝初始化栈
int STACK::size() const noexcept													//返回栈的容量即2m
{
	return q.size() + QUEUE::size();
}
STACK::operator int() const noexcept //返回栈的实际元素个数
{
	return q.operator int() + QUEUE::operator int();
}
STACK& STACK::operator<<(int e) //将e入栈，并返回当前栈
{
	if (QUEUE::operator int() < QUEUE::size() - 1)
	{
		QUEUE::operator<<(e);
		return *this;
	}
	else if (q.operator int() < q.size() - 1)
	{
		int temp;
		QUEUE::operator>>(temp);
		QUEUE::operator<<(e);
		q.operator<<(temp);
		return *this;
	}
	else
		throw "STACK is full!";
}
STACK& STACK::operator>>(int& e) //出栈到e，并返回当前栈
{
	if (QUEUE::operator int())
	{
		int size = QUEUE::operator int(), temp;
		for (int i = 0; i < size - 1; i++)
		{
			QUEUE::operator>>(temp);
			QUEUE::operator<<(temp);
		}
		QUEUE::operator>>(e);
		return *this;
	}
	else if (q.operator int())
	{
		int size = q.operator int(), temp = 0;
		for (int i = 0; i < size - 1; i++)
		{
			q.operator>>(temp);
			q.operator<<(temp);
		}
		q.operator>>(e);
		return *this;
	}
	else
		throw "STACK is empty!";
}
STACK& STACK::operator=(const STACK& s) //深拷贝赋值并返回被赋值栈
{
	QUEUE::operator=((QUEUE&)s);
	q.operator=((QUEUE&)s.q);
	return *this;
}
STACK& STACK::operator=(STACK&& s) noexcept //移动赋值并返回被赋值栈
{
	QUEUE::operator=((QUEUE&&)s);
	q.operator=((QUEUE&&)s.q);
	return *this;
}
char* STACK::print(char* b) const noexcept //从栈底到栈顶打印栈元素
{
	char* temp = new char[size()];
	temp = QUEUE::print(temp);
	b = q.print(b);
	strcat(b, temp);
	printf("%s\n", b);
	delete[] temp;
	return b;
}
STACK::~STACK() noexcept {} //销毁栈