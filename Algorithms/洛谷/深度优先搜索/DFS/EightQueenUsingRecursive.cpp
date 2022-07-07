#include <stdio.h>
#include <math.h>

/*八皇后问题是在8*8的棋盘上放置8枚皇后，使得棋盘中每个横向、纵向、左上至右下斜向、右上至左下斜向均只有一枚皇后。
求解出所有摆法,一共有92种摆法*/

const int N = 8; //棋盘行数
int a[N] = {0}; //表示棋盘，若a[2]=2,则表示在第3行第2列放一个皇后，因为同一行不能放两个皇后，所以只需要1维数组就可以表示一个棋盘。

int solution = 0;//解的个数

//row行，col列, 是否可以摆皇后
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
	printf("第%d种解：\n",++solution);
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