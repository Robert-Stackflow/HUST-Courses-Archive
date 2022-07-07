#include "stdio.h"
void swap(int *p1,int *p2); /* 声明指针参数的交换函数原型*/
int main(void)
{
	int x,y;
	printf("input two integers for x and y please!\n");
	scanf("%d%d",&x,&y); /* 从键盘输入对x,y赋值 */
	printf("before swap,x=%d and y=%d\n",x,y);
	swap(&x,&y); /*以x,y之址为实参*/
	printf("after swap,x=%d and y=%d\n",x,y);
	return 0;
}
void swap(int *p1,int *p2)
{
	int t;
	t=*p1;*p1=*p2;*p2=t; /* 交换指针p1,p2所指变量之值 */
}

