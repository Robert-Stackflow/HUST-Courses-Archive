#include<stdio.h> 
#include<math.h>
long isprime(long n)//定义一个函数判断是素数 
{
	int flag=1;
	for(int i=2;i<=sqrt(n);i++)
	{
			if(n%i==0)
			{
				flag=0;
				break;
			}
	}
	return flag;			
} 
long isMasonNumber(long num)//定义一个函数判断是梅森数 
{
        int flag=0;
		if (((num+1)& (num))==0)
        	flag=1;    
    	return flag;
}
int count(long x)//定义一个求某数是2的几次方的函数 
	{
	int count=0;
	int total=1;
	while(total<x)
	{
    	total = total * 2;
    	++count;
	}
	if (total == x)
    	return count;
}

int main(void)
{
	long i=2,m;
	printf("请输入一个长度大于三的长整数：\n");
	scanf("%d",&m);
	for(;i<=m;++i)
	{
		if(isMasonNumber(i))//if循环的嵌套，先判断是素数，再判断是否为梅森素数 
		{
			if(isprime(i))

				printf("M(%d)=%ld\n",count(i+1),i);//按示例输出 	
		}
	}
	return 0; 
}
