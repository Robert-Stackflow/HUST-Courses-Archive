#include "stdio.h"
#define SIZE 2
int main(void)
{	int x[SIZE][SIZE+1];
	int i,j;
	for(i=0;i<SIZE;i++){
		for(j=0;j<SIZE;j++)
			scanf("%d",&x[i][j]);/*输入成绩*/
		x[i][SIZE]=(x[i][0]+x[i][1])/2;/*计算学生的平均成绩*/
	}
	printf("\n");
	for(i=0;i<SIZE;i++){
		for(j=0;j<SIZE+1;j++)
			printf("%p\tx[%d][%d]=%d\t",&x[i][j],i,j,x[i][j]);/*输出成绩*/
		printf("\n");
	}
	return 0;
}
