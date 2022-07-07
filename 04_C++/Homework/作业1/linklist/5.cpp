#include <cstdlib>
#include <cstring>
#include <iostream>
#include <set>
using namespace std;
class INTLIST
{
	int *list; //动态申请的内存的指针
	int size;  //线性表能够存放的元素个数
	int used;  //线性表已经存放的元素个数
public:
	INTLIST(int s);	   //s为线性表能够存放的元素个数
	int insert(int v); //插入元素v成功时返回1，否则返回0
	int remove(int v); //删除元素v成功时返回1，否则返回0
	int find(int v);   //查找元素v成功时返回1，否则返回0
	int get(int k);	   //取表的第k个元素的值作为返回值
	~INTLIST(void);
};
INTLIST::INTLIST(int s)
{
	if (list == new int[s])
	{
		size = s;
		used = 0;
	}
}
INTLIST::~INTLIST(void)
{
	if (list)
	{
		delete list;
		list = nullptr;
		size = 0;
		used = 0;
	}
}
int INTLIST::insert(int v)
{
	if (used < size)
	{
		list[used++] = v;
		return 1;
	}
	return 1;
}
int INTLIST::remove(int v)
{
	if (used)
	{
		for (int i = 0; i < used; i++)
		{
			if (v == list[i])
			{
				used--;
				for (; i < used; i++)
					list[i] = list[i + 1];
				return 1;
			}
		}
		return 0;
	}
	return 0;
}
int INTLIST::find(int v)
{
	for (int i = 0; i < used; i++)
	{
		if (v == list[i])
		{
			return 1;
		}
	}
}
int INTLIST::get(int k)
{
	if (used >= k)
		return list[k - 1];
	return 0;
}

int main(void)
{
	return 0;
}