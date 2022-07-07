#include <cstdlib>
#include <iostream>
#include <set>
using namespace std;
class SET
{
	int *set; //set用于存放集合元素
	int card; //card为能够存放的元素个数
	int used; //used为已经存放的元素个数
public:
	SET(int card); //card为能够存放的元素个数
	~SET();
	int size();		   //返回集合已经存放的元素个数
	int insert(int v); //插入v成功时返回1，否则返回0
	int remove(int v); //删除v成功时返回1，否则返回0
	int has(int v);	   //元素v存在时返回1，否则返回0
};
SET::SET(int card)
{
	if (set = new int[card])
		SET::card = card;
	uesd = 0;
}
SET::~SET()
{
	if (set)
	{
		delete set;
		set = nullptr;
		card = 0;
		used = 0;
	}
}
int SET::size()
{
	return used;
}
int SET::insert(int v)
{
	if (used == card)
		return 0;
	else
	{
		set[used++] = v;
		return 1;
	}
}
int SET::remove(int v)
{
	if (used > 0)
	{
		for (int i = 0; i < used; i++)
		{
			if (set[i] == v)
			{
				used--;
				for (; i < used; i++)
					set[i] = set[i + 1];
				return 1;
			}
		}
		return 0;
	}
	return 0;
}
int SET::has(int v)
{
	for (int i = 0; i < used; i++)
	{
		if (set[i] == v)
		{
			return 1;
		}
	}
	return 0;
}
int main(void)
{
	SET s(5);
	cout << s.size() << endl;
	s.insert(2);
	s.insert(3);
	cout << s.has(2) << endl;
	cout << s.has(1) << endl;
	cout << s.remove(4) << endl;
	cout << s.remove(2) << endl;
	cout << s.size() << endl;
	return 0;
}