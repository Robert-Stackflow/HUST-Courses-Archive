#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*打印螺旋方阵
请输入数组长度:5
 1  2  3  4  5
16 17 18 19  6
15 24 25 20  7
14 23 22 21  8
13 12 11 10  9
*/
int main()
{
	int num = 1;
	int n = 0;
	int i, j;int nextI, nextJ = 0;
	//Right,Down,Left,Up  
	int direction[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
	//当前的方向
	int d = 0;

	printf("请输入数组长度:");
	scanf("%d", &n);
	int **matrix = (int **)malloc(sizeof(int) * n);
	for (i = 0; i < n; i++)
	{
		matrix[i] = (int *)malloc(sizeof(int) * n);
	}
	//memset(matrix, 0, sizeof(int) * n * n); not work

	//清0
	for (i = 0; i < n; i++)
	{
		memset(matrix[i], 0, sizeof(int) * n);
	}

	i = j = 0;
	while (num <= n * n)
	{
		matrix[i][j] = num;
		nextI = i + direction[d][0];
		nextJ = j + direction[d][1];
		//若出界，或者下一步已经走过，则转方向
		if (nextI < 0 || nextI >= n || nextJ < 0 || nextJ >= n || matrix[nextI][nextJ] !=0)
		{
			//转方向
			d = (d + 1) %4;
		}
		//准备下一步
		i = i + direction[d][0];
		j = j + direction[d][1];
		num++;
	}

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			printf("%3d", matrix[i][j]);
		}
		printf("\n");
	}

	return 0;
}

