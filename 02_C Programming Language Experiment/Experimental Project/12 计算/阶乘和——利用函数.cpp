#include<stdio.h>
/*关键是编写一个求阶乘的函数*/ 
/*学会运用for循环结构*/
/*学会运用能够防止溢出的数据类型*/ 
/*学会区别++i与i++的不同*/
long long factorial(long long n){
	if (n==0||n==1)
		return 1;
	else
		return n*factorial(n-1);
}
int main(void)
{
	long long n,sum=0;
	printf("请输入一个正整数n=");
	while(scanf("%d",&n)!=EOF){
		for(;n!=0;--n)
		sum+=factorial(n);
		printf("您所求的阶乘和是%lld\n",sum);
		printf("请输入一个正整数n=");
		sum=0;
	}
	
	return 0;
}
