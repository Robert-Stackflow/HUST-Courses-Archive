#include<stdio.h> 
#include<math.h> 
#include<string.h>

int main(void)
{
	int m,n,flag,count=0;
	scanf("%d",&m);
	int a[50];
	if(m>=0)//�ж�������������������䣬����Ǹ�������ݶ�����ԭ�������Ӧֵ 
		n=m;
	else
		n=m+(int)pow(2,32)+1;	
	for(int j=0;j<32;j++)//���ó���ȡ�෨���ν������ƴӵ�λ����λ�������� 
	{
		flag=n%2;
		n=(int)(n/2);
		count++;
		a[j]=flag;
	} 
	if(m<0)//���С���㣬��ѷ���λ��Ϊ1 
		a[31]=1;
	for(int j=count-1;j>=0;j--)//�Ӹ�λ����λ��������� 
	{
		if(j!=0&&(j+1)%4==0&&(j+1)!=32)
			printf(" ");//ʵ�ְ���ʽ��� 
		printf("%d",a[j]);
	}
		
	printf("\n");
	return 0;
}
