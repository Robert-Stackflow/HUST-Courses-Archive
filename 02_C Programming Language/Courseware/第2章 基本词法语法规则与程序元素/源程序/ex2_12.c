#include<stdio.h>
#define N  10
int main(void)
{
	int i,sum;    /* i是循环变量，sum是累加器变量，存放和值 */
    i=1;          /* 循环变量初始化为1  */
	sum=0;        /* 累加器初始化为0  */
	while(i<=N)   /* 循环求和 1+2+...+N */
		sum+=i++;          /* 等价于 sum=sum+i,i++; */
	printf("sum=%d\n",sum);  /* 输出和值 */
	return 0;
}
