#include "Queue.h"
QUEUE::QUEUE(int m) : max(m), elems(new int[m]), head(0), tail(0) {}			   //初始化队列：最多申请m个元素
QUEUE::QUEUE(const QUEUE& q) : max(q.max), elems(new int[q.max]), head(0), tail(0) //用q深拷贝初始化队列
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
QUEUE::QUEUE(QUEUE&& q) noexcept : max(q.max), elems(nullptr), head(0), tail(0) //用q移动初始化队列
{
	head = q.head;
	tail = q.tail;
	*(const_cast<int*>(&max)) = q.max;
	*(const_cast<int**>(&elems)) = q.elems;
	*(const_cast<int*>(&q.max)) = 0;
	*(const_cast<int**>(&q.elems)) = nullptr;
	q.head = q.tail = 0;
}
QUEUE::operator int() const noexcept //返回队列的实际元素个数
{
	if (max == 0)
		return 0;
	return (tail - head + max) % max;
}
int QUEUE::size() const noexcept //返回队列申请的最大元素个数max
{
	return max;
}
QUEUE& QUEUE::operator<<(int e) //将e入队列尾部，并返回当前队列
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
QUEUE& QUEUE::operator>>(int& e) //从队首出元素到e，并返回当前队列
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
QUEUE& QUEUE::operator=(const QUEUE& q) //深拷贝赋值并返回被赋值队列
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
QUEUE& QUEUE::operator=(QUEUE&& q) noexcept //移动赋值并返回被赋值队列
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
char* QUEUE::print(char* s) const noexcept //打印队列至s并返回s
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
QUEUE::~QUEUE() //销毁当前队列
{
	if (elems == nullptr)
		return;
	head = tail = 0;
	*(const_cast<int*>(&max)) = 0;
	delete[] elems;
	*(const_cast<int**>(&elems)) = nullptr;
}