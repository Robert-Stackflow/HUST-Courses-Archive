#include <cstdlib>
#include <cstring>
#include <iostream>
#include <set>
using namespace std;
class NODE
{
	char *data;
	NODE *left, *right;

public:
	NODE(char *);
	NODE(char *data, NODE *left, NODE *right);
	~NODE();
};
NODE::NODE(char *)
{
	if (NODE::data = new char[strlen(data) + 1])
	{
		strcpy(NODE::data, data);
		left = right = nullptr;
	}
}
NODE::NODE(char *data, NODE *left, NODE *right)
{
	if (NODE::data = new char[strlen(data) + 1])
	{
		strcpy(NODE::data, data);
		NODE::left = left;
		NODE::right == right;
	}
}
NODE::~NODE(){
	if(left)
		left->~NODE();
	if(right)
		right->~NODE();
	if(data){
		delete data;
		data = nullptr;
	}
}
int main(void)
{
	return 0;
}