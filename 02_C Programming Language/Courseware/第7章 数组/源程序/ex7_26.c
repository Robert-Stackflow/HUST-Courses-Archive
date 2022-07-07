#include "stdio.h"
int BinarySearch(int a[],int x,int n);
int main(void)
{
	int x[]={1,3,5,7,9,11,13,15,17,19},index;
	index=BinarySearch(x,11,10);/*调用二分查找函数*/
	if(index!=-1)
		printf("find %d!\n",x[index]);
	else
		printf("not find!\n");
	return 0;
}
int BinarySearch(int a[],int x,int n)/*定义二分查找函数*/
{	int front=0,back=n-1,middle;
	while(front<=back) {
		middle=(front+back)/2;   /* 计算中间单元的下标 */
		if(x<a[middle])
			back=middle-1;	/* 修改前半部分的最后元素的下标为middle-1*/
		else if(x>a[middle])
			front=middle+1; /* 修改后半部分的最前面元素的下标为middle+1 */
		else
			return (middle); /* 找到，返回该数所在单元的下标 */
	}
	return -1;               /* 没有找到，返回-1 */
}
