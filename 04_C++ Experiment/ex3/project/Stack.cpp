#include "Stack.h"
STACK::STACK(int m) : QUEUE(m), q(QUEUE(m)) {}										//��ʼ��ջ�������2m-2��Ԫ��
STACK::STACK(const STACK& s) : QUEUE(s), q(QUEUE(s.q)) {}							//��ջs�����ʼ��ջ
STACK::STACK(STACK&& s) noexcept : QUEUE((QUEUE&&)s), q(QUEUE((QUEUE&&)s.q)) {} //��ջs�ƶ�������ʼ��ջ
int STACK::size() const noexcept													//����ջ��������2m
{
	return q.size() + QUEUE::size();
}
STACK::operator int() const noexcept //����ջ��ʵ��Ԫ�ظ���
{
	return q.operator int() + QUEUE::operator int();
}
STACK& STACK::operator<<(int e) //��e��ջ�������ص�ǰջ
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
STACK& STACK::operator>>(int& e) //��ջ��e�������ص�ǰջ
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
STACK& STACK::operator=(const STACK& s) //�����ֵ�����ر���ֵջ
{
	QUEUE::operator=((QUEUE&)s);
	q.operator=((QUEUE&)s.q);
	return *this;
}
STACK& STACK::operator=(STACK&& s) noexcept //�ƶ���ֵ�����ر���ֵջ
{
	QUEUE::operator=((QUEUE&&)s);
	q.operator=((QUEUE&&)s.q);
	return *this;
}
char* STACK::print(char* b) const noexcept //��ջ�׵�ջ����ӡջԪ��
{
	char* temp = new char[size()];
	temp = QUEUE::print(temp);
	b = q.print(b);
	strcat(b, temp);
	printf("%s\n", b);
	delete[] temp;
	return b;
}
STACK::~STACK() noexcept {} //����ջ