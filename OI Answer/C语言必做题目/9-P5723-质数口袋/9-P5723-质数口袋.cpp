#include<stdio.h>
#include<math.h>
int isprime(int n)
{
	int flag=1;
	for(int i=2;i<=sqrt(n);i++)
		if(n%i==0){flag=0;break;}
	return flag;			
}//判断是否为素数 
int main(void)
{
	int L,count=0,sum=0;
	scanf("%d",&L);
	for(int i=2;;i++)
	{
		if(isprime(i))sum+=i;
		if(sum>L) break;//判断当前的和与限制值的大小 
		if(isprime(i)){printf("%d\n",i);count++;}
	}
	printf("%d",count);
}
//缺点：当L的值很大时容易TLE
//下面是埃氏筛法的C代码
int prime[100007]={1};
int l;
void ai() {
	for(int i=2;i<=100000;++i)
		if(prime[i])
			for(int j=i*2;j<=100000;j+=i)
				prime[j]=0;	
}
int main() {
	scanf("%d",&l);
	int p = l, sum = 0;
	ai();
	for(int i = 1; i <= p; ++i) {
		if(prime[i]) {
			printf("%d\n", i);
			p -= i;
			sum++;
		}
		if(p <= 0)	break;
	} 
	printf("%d", sum);
	return 0;
} 
