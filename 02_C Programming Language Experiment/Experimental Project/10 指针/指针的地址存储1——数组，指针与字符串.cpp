#include<stdio.h>
int main(void){
//数组和指针
	printf("---数组和指针---\n\n");
	int nums[]={1,2,3};
	int *p1=nums;
	//此时nums==p1==&nums==&nums[0] 
	//数组名就是该数组的地址，此时nums[]可写为p1[]
	//如下输出：
	printf("%d\t%d\t%d\n\n",p1[0],p1[1],p1[2]); 
//指针类型要和变量类型对应 
	/*int intvalue=1230;
	char charvalue='1';
	int *pint;
	//注意此时的赋值，这是不合法的，会报错 
	//*pint=&charvalue;
	char *pchar;
	//*pchar=&intvalue;
	printf("%d",*pint);
	printf("%d",*pchar);*/
//多重指针
	printf("---多重指针---\n\n");
	int num=10;	
	int *nump=&num;
	int **numpp=&nump;
	int ***numppp=&numpp;
	printf("%d\t%d\t%d\n\n",*nump,**numpp,***numppp);
//指针的移动
	printf("---指针的移动---\n\n");
	int nums1[]={1,2,3};
	int *p2=nums1;
	printf("nums1[i]:\t");
	for(int i=0;i<3;i++)
		printf("%d ",nums1[i]); 
	printf("\n");
	printf("p2[i]:\t\t");
	for(int i=0;i<3;i++)
		printf("%d ",p2[i]); 
	printf("\n");
	printf("*(p2+i):\t");
	for(int i=0;i<3;i++)
		printf("%d ",*(p2+i));
	printf("\n");
	printf("*(nums1+i):\t");
	for(int i=0;i<3;i++)
		printf("%d ",*(nums1+i));
	printf("\n\n");
//指针和字符串
	printf("---指针和字符串---\n\n");
	char*p="cs";
	printf("%s\n",p);
	printf("%c%c\n\n",p[0],p[1]);
	//p[1]='d';
	//用指针存储字符串，存储在常量静态区，但不可修改字符串。
	//用数组存储字符串，则存储在栈中，可以修改字符串，但执行完后会被释放。
	//多个相同的值对应一个地址，且不会被释放。
	//printf("%s",p);
}
