#include<stdio.h>
#include<math.h>
int isprime(int n)
{
	int flag=1;
	for(int i=2;i<=sqrt(n);i++)
		if(n%i==0){flag=0;break;}
	return flag;			
}//�ж��Ƿ�Ϊ���� 
int main(void)
{
	int L,count=0,sum=0;
	scanf("%d",&L);
	for(int i=2;;i++)
	{
		if(isprime(i))sum+=i;
		if(sum>L) break;//�жϵ�ǰ�ĺ�������ֵ�Ĵ�С 
		if(isprime(i)){printf("%d\n",i);count++;}
	}
	printf("%d",count);
}
//ȱ�㣺��L��ֵ�ܴ�ʱ����TLE
//�����ǰ���ɸ����C����
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
