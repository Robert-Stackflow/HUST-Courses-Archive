#include<stdio.h>
/*�ؼ��Ǳ�дһ����׳˵ĺ���*/ 
/*ѧ������forѭ���ṹ*/
/*ѧ�������ܹ���ֹ�������������*/ 
/*ѧ������++i��i++�Ĳ�ͬ*/
long long factorial(long long n){
	if (n==0||n==1)
		return 1;
	else
		return n*factorial(n-1);
}
int main(void)
{
	long long n,sum=0;
	printf("������һ��������n=");
	while(scanf("%d",&n)!=EOF){
		for(;n!=0;--n)
		sum+=factorial(n);
		printf("������Ľ׳˺���%lld\n",sum);
		printf("������һ��������n=");
		sum=0;
	}
	
	return 0;
}
