#include <stdio.h>
#include <math.h>
#include <stack>
using namespace std;
/*�˻ʺ���������8*8�������Ϸ���8ö�ʺ�ʹ��������ÿ��������������������б������������б���ֻ��һö�ʺ�*/

const int N = 8; //��������
int a[N] = {0}; //��ʾ���̣���a[2]=2,���ʾ�ڵ�3�е�2�з�һ���ʺ���Ϊͬһ�в��ܷ������ʺ�����ֻ��Ҫ1ά����Ϳ��Ա�ʾһ�����̡�

int solution = 0;//��ĸ���

struct Node
{
	int row;
	int col;
};

//row�У�col��, �Ƿ���԰ڻʺ�
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

//��ӡ�����н�
void Print()
{
	printf("��%d�ֽ⣺\n", ++solution);
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
				//��ok�Ľڵ�ŵ���ǰ��
				a[node.row] = node.col;
				stack.pop();
				stack.push(node);
				
				//������һ��ĵ�һ���ڵ�
				node.row++;
				node.col = 0;
				stack.push(node);
			}
			else
			{
				//--done
				a[node.row] = node.col;
				Print();
				
				//���뵱ǰ�����һ�����
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

