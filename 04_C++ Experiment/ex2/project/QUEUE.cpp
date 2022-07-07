#include "Queue.h"
QUEUE::QUEUE(int m) : max(m), elems(new int[m]), head(0), tail(0) {}			   //��ʼ�����У��������m��Ԫ��
QUEUE::QUEUE(const QUEUE& q) : max(q.max), elems(new int[q.max]), head(0), tail(0) //��q�����ʼ������
{
	head = q.head;
	tail = q.tail;
	if (head != tail)
	{
		int** ptemp = const_cast<int**>(&elems);
		for (int i = head; i != tail; i++)
		{
			if (i == max)
				i = 0;
			if (i == tail)
				break;
			if ((*ptemp + i) != nullptr)
				*(*ptemp + i) = q.elems[i];
		}
	}
}
QUEUE::QUEUE(QUEUE&& q) noexcept : max(q.max), elems(nullptr), head(0), tail(0) //��q�ƶ���ʼ������
{
	head = q.head;
	tail = q.tail;
	*(const_cast<int*>(&max)) = q.max;
	*(const_cast<int**>(&elems)) = q.elems;
	*(const_cast<int*>(&q.max)) = 0;
	*(const_cast<int**>(&q.elems)) = nullptr;
	q.head = q.tail = 0;
}
QUEUE::operator int() const noexcept //���ض��е�ʵ��Ԫ�ظ���
{
	if (max == 0)
		return 0;
	return (tail - head + max) % max;
}
int QUEUE::size() const noexcept //���ض�����������Ԫ�ظ���max
{
	return max;
}
QUEUE& QUEUE::operator<<(int e) //��e�����β���������ص�ǰ����
{
	if ((tail + 1) % max == head)
		throw "QUEUE is full!";
	else
	{
		elems[tail++] = e;
		if (tail == max)
			tail = 0;
		return *this;
	}
}
QUEUE& QUEUE::operator>>(int& e) //�Ӷ��׳�Ԫ�ص�e�������ص�ǰ����
{
	if (head == tail)
		throw "QUEUE is empty!";
	else
	{
		e = elems[head++];
		if (head == max)
			head = 0;
		return *this;
	}
}
QUEUE& QUEUE::operator=(const QUEUE& q) //�����ֵ�����ر���ֵ����
{
	if (elems != nullptr && elems != q.elems)
	{
		delete[] elems;
		*(const_cast<int**>(&elems)) = nullptr;
	}
	if (elems == q.elems)
		return *this;
	head = q.head;
	tail = q.tail;
	*(const_cast<int*>(&max)) = q.max;
	*(const_cast<int**>(&elems)) = new int[max];
	if (head != tail)
	{
		int** ptemp = const_cast<int**>(&elems);
		for (int i = head; i != tail; i++)
		{
			if (i == max)
				i = 0;
			if (i == tail)
				break;
			if ((*ptemp + i) != nullptr)
				*(*ptemp + i) = q.elems[i];
		}
	}
	return *this;
}
QUEUE& QUEUE::operator=(QUEUE&& q) noexcept //�ƶ���ֵ�����ر���ֵ����
{
	if (elems != nullptr && elems != q.elems)
	{
		delete[] elems;
		*(const_cast<int**>(&elems)) = nullptr;
	}
	if (elems == q.elems)
		return *this;
	head = q.head;
	tail = q.tail;
	*(const_cast<int*>(&max)) = q.max;
	*(const_cast<int**>(&elems)) = q.elems;
	*(const_cast<int*>(&q.max)) = 0;
	*(const_cast<int**>(&q.elems)) = nullptr;
	q.head = q.tail = 0;
	return *this;
}
char* QUEUE::print(char* s) const noexcept //��ӡ������s������s
{
	s[0] = '\0';
	for (int i = head; i != tail; i++)
	{
		if (i == max)
			i = 0;
		if (i == tail)
			break;
		char* temp = s + strlen(s);
		sprintf(temp, "%d,", this->elems[i]);
	}
	return s;
}
QUEUE::~QUEUE() //���ٵ�ǰ����
{
	if (elems == nullptr)
		return;
	head = tail = 0;
	*(const_cast<int*>(&max)) = 0;
	delete[] elems;
	*(const_cast<int**>(&elems)) = nullptr;
}