#include<stdio.h>
#include<math.h>
int n,k;
int isprime(int n)
{
	for(int i=2;i<=sqrt(n);i++)
		if(n%i==0)return0;
	return 1;
}//判断是否为素数 
int create(int a,int k,int prior,int *num)
{//a指示当前的升序初始值，避免出现重复
//k指示剩余的需要再取的数
//prior为前面累加的和
//num为传入的数组
	int res=0;
	if(!k)	return isprime(prior);
	//如何需要再取的数已归零，则返回累加和是否为素数
	for(int i=a;i<n;i++)
		res+=create(i+1,k-1,prior+num[i],num);
		//递归下一个过程，把当前的初始值加一，需再取的数减一
		//同时更新已得到的累加和
	return res;
	//调用递归生成全组合，在过程中逐渐把K个数相加
	//当选取的数个数为0时，直接返回前面的累加和是否为质数
}
int main(void)
{
	scanf("%d%d",&n,&k);
	int num[n];
	for(int i=0;i<n;i++)scanf("%d",&num[i]);
	//读入数据
	printf("%d",create(0,k,0,num));
}
