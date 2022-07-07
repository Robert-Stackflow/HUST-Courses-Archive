#include<stdio.h>
#include<stdlib.h>
int main(void)
{
	int number;
	printf("请输入一个数字：");
	scanf("%d",&number);
	int *a=(int *)malloc(number*sizeof(int));
	//分配动态存储空间
//	printf("%d\n",sizeof(a));
//	printf("%d\n",sizeof(*a));
	for(int i=0;i<number;i++)
		scanf("%d",(a+i));
	for(int i=0;i<number;i++)
		printf("%d ",*(a+i));
	free(a);//释放动态存储空间
	//释放存储空间后将无法再次正确输出指针指向的内容
	for(int i=0;i<number;i++)
		printf("\n!!%d!!",*(a+i));
//	free(a);//不可以重复释放动态存储空间
}
