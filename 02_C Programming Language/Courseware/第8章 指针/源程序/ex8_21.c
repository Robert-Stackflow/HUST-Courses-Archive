#include "stdio.h"
int main(void)
{	int x0[5],x1[5],x2[5],x3[5],x4[5];/*声明5个一维数组*/
	int *p[5],i,j;/*声明指针数组p*/
	p[0]=x0;p[1]=x1;p[2]=x2,p[3]=x3,p[4]=x4;/*对指针数组成员赋值*/
	for(i=0;i<5;i++)
		for(j=0;j<5;j++)
			if(i==j) p[i][j]=1;/*用p表示二维数组,对元素赋值*/
			else p[i][j]=0;
	for(i=0;i<5;i++){
		for(j=0;j<5;j++)
			printf("%4d",p[i][j]);/*指针数组表示二维数组元素*/
		printf("\n");
	}
	return 0;
}
