#include <stdio.h>
#include <math.h>

/*�˻ʺ���������8*8�������Ϸ���8ö�ʺ�ʹ��������ÿ��������������������б������������б���ֻ��һö�ʺ�
�������аڷ�,һ����92�ְڷ�*/

const int N = 8; //��������
int a[N] = {0}; //��ʾ���̣���a[2]=2,���ʾ�ڵ�3�е�2�з�һ���ʺ���Ϊͬһ�в��ܷ������ʺ�����ֻ��Ҫ1ά����Ϳ��Ա�ʾһ�����̡�

int solution = 0;//��ĸ���

//row�У�col��, �Ƿ���԰ڻʺ�
bool IsOK(int row, int col)
{
	for (int i = 0; i < row; i++)
	{
		if (a[i] == col || (abs(a[i] - col) == row - i))
		{
			return false;
		}
	}
	return true;
}

void Display()
{
	printf("��%d�ֽ⣺\n",++solution);
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

void DSF(int row)
{
	for (int col = 0; col < N; col++)
	{
		//find
		if (IsOK(row, col))
		{
			a[row] = col;
			//forward
			if (row != N -1)
			{
				DSF(row + 1);
			}
			else
			{
				//done
				Display();
			}
			
		}
	}
	//back
}

int main()
{
	DSF(0);
	return 0;
}