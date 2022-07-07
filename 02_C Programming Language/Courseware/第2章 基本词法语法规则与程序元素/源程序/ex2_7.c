#include<stdio.h>
int main(void)
{
	int x,i,j,k; /* x是三位数，i,j,k分别是组成x的三个数字 */
    for(x=100;x<=999;x=x+1)   /* 从100开始循环到999 */
	{
		i=x/100;          /* 分解百位数 */
		j=(x-i*100)/10;   /* 分解十位数 */
		k=x%10;           /* 分解个位数 */
		if(x==i*i*i+j*j*j+k*k*k) /* 是水仙花数 */
			printf("%5d",x);  /* 输出 */
	}
	return 0;
}
