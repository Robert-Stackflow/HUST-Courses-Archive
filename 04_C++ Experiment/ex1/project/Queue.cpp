#include "Queue.h"
void initQueue(Queue* const p, int m) //初始化p指队列：最多申请m个元素
{
	p->head = 0;
	p->tail = 0;
	int* temp = const_cast<int*>(&p->max);
	*temp = m;
	int** ptemp = const_cast<int**>(&p->elems);
	*ptemp = (int*)malloc(sizeof(int) * m);
}

void initQueue(Queue* const p, const Queue& s) //用s深拷贝初始化p指队列
{
	p->head = s.head;
	p->tail = s.tail;
	int* temp = const_cast<int*>(&p->max);
	*temp = s.max;
	int** ptemp = const_cast<int**>(&p->elems);
	*ptemp = (int*)malloc(sizeof(int) * (p->max));
	if (p->head != p->tail)
	{
		int** ptemp = const_cast<int**>(&p->elems);
		for (int i = p->head; i != p->tail; i++)
		{
			if (i == p->max)
				i = 0;
			if ((*ptemp + i) != NULL)
				*(*ptemp + i) = s.elems[i];
		}
	}
}

void initQueue(Queue* const p, Queue&& s) //用s移动初始化p指队列
{
	p->head = s.head;
	p->tail = s.tail;
	int* temp = const_cast<int*>(&p->max);
	*temp = s.max;
	int** ptemp = const_cast<int**>(&p->elems);
	*ptemp = s.elems;
	ptemp = const_cast<int**>(&s.elems);
	*ptemp = NULL;
	s.head = 0;
	s.tail = 0;
	temp = const_cast<int*>(&s.max);
	*temp = 0;
}
int number(const Queue* const p) //返回p指队列的实际元素个数
{
	if (p->max == 0)
		return 0;
	return (p->tail - p->head + p->max) % p->max;
}
int size(const Queue* const p) //返回p指队列申请的最大元素个数max
{
	return p->max;
}
Queue* const enter(Queue* const p, int e) //将e入队列尾部，并返回p
{
	if ((p->tail + 1) % p->max == p->head)
		throw "Queue is full!";
	else
	{
		p->elems[p->tail++] = e;
		if (p->tail == p->max)
			p->tail = 0;
		return p;
	}
}
Queue* const leave(Queue* const p, int& e) //从队首出元素到e，并返回p
{
	if (p->head == p->tail)
		throw "Queue is empty!";
	else
	{
		e = p->elems[p->head++];
		if (p->head == p->max)
			p->head = 0;
		return p;
	}
}
Queue* const assign(Queue* const p, const Queue& q) //深拷贝赋s给队列并返回p
{
	if (p->elems != NULL && p->elems != q.elems)
	{
		free(p->elems);
		int** ptemp = const_cast<int**>(&p->elems);
		*ptemp = NULL;
	}
	if (p->elems == q.elems)
	{
		return p;
	}
	p->head = q.head;
	p->tail = q.tail;
	int* temp = const_cast<int*>(&p->max);
	*temp = q.max;
	int** ptemp = const_cast<int**>(&p->elems);
	*ptemp = (int*)malloc(sizeof(int) * (p->max));
	if (p->head == p->tail)
		return p;
	for (int i = p->head; i != p->tail; i++)
	{
		if (i == p->max)
			i = 0;
		if ((*ptemp + i) != NULL)
			*(*ptemp + i) = q.elems[i];
	}
	return p;
}
Queue* const assign(Queue* const p, Queue&& q) //移动赋s给队列并返回p
{
	if (p->elems != NULL && p->elems != q.elems)
	{
		free(p->elems);
		int** ptemp = const_cast<int**>(&p->elems);
		*ptemp = NULL;
	}
	if (p->elems == q.elems)
	{
		return p;
	}
	p->head = q.head;
	p->tail = q.tail;
	int* temp = const_cast<int*>(&p->max);
	*temp = q.max;
	int** ptemp = const_cast<int**>(&p->elems);
	*ptemp = q.elems;
	ptemp = const_cast<int**>(&q.elems);
	*ptemp = NULL;
	q.head = 0;
	q.tail = 0;
	temp = const_cast<int*>(&q.max);
	*temp = 0;
	return p;
}
char* print(const Queue* const p, char* s)
{
	for (int i = p->head; i != p->tail; i++)
	{
		if (i == p->max)
			i = 0;
		char* temp = s + strlen(s);
		sprintf(temp, "%d,", p->elems[i]);
	}
	return s;
}
void destroyQueue(Queue* const p) //销毁p指向的队列
{
	if (p->elems == NULL)
		return;
	p->head = 0;
	p->tail = 0;
	int* temp = const_cast<int*>(&p->max);
	*temp = 0;
	free(p->elems);
	int** ptemp = const_cast<int**>(&p->elems);
	*ptemp = NULL;
}