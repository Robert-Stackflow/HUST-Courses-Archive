#include "stdio.h"
void swap(int u,int v); /* 声明交换函数原型*/
int main(void)
{
	int x,y; /* 声明整型变量x,y*/
	printf("input two integers for x and y please!\n");
	scanf("%d%d",&x,&y); /* 从键盘输入对x,y赋值 */
	printf("in function main, before swap,x=%d and y=%d\n",x,y);
	swap(x,y); /* 以x,y之值为实参调用交换函数 */
	printf("in function main, after swap,x=%d and y=%d\n",x,y);
	return 0;
}
void swap(int u,int v) /* 定义交换函数 */
{
	int t; /* 声明局部整型变量t */
	printf("in function swap, before swap,u=%d and v=%d\n",u,v);
	t=u;u=v;v=t; /* 交换u,v之值 */
	printf("in function swap, after swap,u=%d and v=%d\n",u,v);
}

