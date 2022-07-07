#include "stdio.h"
int a1(int);
int a2(int);
int main(void)/*fpa是有2个元素的函数指针数组，每个元素指向*/
{	int i,(*fpa[2])(int);/*的函数有一个整型形参，返回整型值*/
	fpa[0]=a1;/*第1个（下标为0）元素指向a1函数*/
	fpa[1]=a2;/*第2个（下标为1）元素指向a2函数*/
	for(i=0;i<2;i++)
		printf("%d\n",fpa[i]((i+1)*5));/*依次调用fpa[0]、fpa[1]所指函数*/
	return 0;
}
int a1(int x){
	printf("in function a1,x=%d\n",x);
	return 2*x;
}
int a2(int y){
	printf("in function a2,y=%d\n",y);
	return 2*y;
}
