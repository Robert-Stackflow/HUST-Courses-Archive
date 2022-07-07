#include "stdio.h"
void bubble_sort(int a[],int n);/*冒泡排序函数原型声明*/
int main(void)
{	int x[]={31,25,12,86,42,6};
	bubble_sort(x,6); /*调用冒泡排序函数，实参用数组名，并给出元素个数*/
	return 0;
}
void bubble_sort(int a[],int n)     /*定义冒泡排序函数，形参用形式数组a[]*/
{	int i,j,t,k;
	for(i=0;i<n-1;i++){             /* 共进行n-1轮"冒泡" */	
		for(j=0;j<n-i-1;j++)		/*控制每一轮冒泡的循环*/
		   if(a[j]>a[j+1])          /*对两两相邻的元素进行比较*/
			   t=a[j],a[j]=a[j+1],a[j+1]=t; /*如果a[j]>a[j+1]，则交换*/
		for(k=0;k<n;k++)            /*输出每一轮"冒泡"排序后的结果*/
			printf("%d  ",a[k]);
		printf("\n");
	}
}