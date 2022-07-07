#include <stdio.h>
#include <math.h>
#include <stack>
using namespace std;
/*八皇后问题是在8*8的棋盘上放置8枚皇后，使得棋盘中每个横向、纵向、左上至右下斜向、右上至左下斜向均只有一枚皇后*/

const int N = 8; //棋盘行数
int a[N] = {0}; //表示棋盘，若a[2]=2,则表示在第3行第2列放一个皇后，因为同一行不能放两个皇后，所以只需要1维数组就可以表示一个棋盘。

int solution = 0;//解的个数

struct Node
{
	int row;
	int col;
};

//row行，col列, 是否可以摆皇后
bool IsOK(Node node)
{
	for (int i = 0; i < node.row; i++)
	{
		if (a[i] == node.col || (abs(a[i] - node.col) == node.row - i))
		{
			return false;
		}
	}
	return true;
}

//打印出所有解
void Print()
{
	printf("第%d种解：\n", ++solution);
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (a[i] == j)
			{
				printf("%d", i);
			}
			else
			{
				printf("#");
			}
		}
		printf("\n");
	}

	printf("-----------------\n");
}

void DSF()
{
	Node node;
	stack<Node> stack;

	node.row = 0;
	node.col = 0;
	stack.push(node);
	while(stack.size() >= 1)
	{
		//--find
		node = stack.top();
		while (node.col < N && !IsOK(node))
		{
			node.col++;
		}

		if (node.col < N)
		{
			//--forward
			if (node.row < N-1)
			{
				//把ok的节点放到当前层
				a[node.row] = node.col;
				stack.pop();
				stack.push(node);
				
				//进入下一层的第一个节点
				node.row++;
				node.col = 0;
				stack.push(node);
			}
			else
			{
				//--done
				a[node.row] = node.col;
				Print();
				
				//进入当前层的下一个结点
				//node = stack.top();
				node.col++;
				stack.pop();
				stack.push(node);
			}
		}
		else
		{
			//--back
			stack.pop();
			
			if (stack.size() == 0)
			{
				return;
			}
			node = stack.top();
			node.col++;
			stack.pop();
			stack.push(node);

		}

	}

}

int main()
{
	DSF();
	return 0;
}

