#include <stdio.h>
int main()
{ 
	int i,j,n=0,a[17]={0,1},l,r;
	while(n<1||n>16)
    { 
	printf("��������������ε�����:");
	scanf("%d",&n);
	}
	for(i=1;i<=n;i++)
	{ 
		l=0;
	for(j=1;j<=i;j++)
	{ 
		r=a[j];
		a[j]=l+r; /*ÿ��������������֮��*/
		l=r;
		printf("%5d",a[j]); 
		printf(" ");
	}
		printf("\n");
	}
}
//�ⷨ��ֻʹ����һ��һά�����������ʱ������
