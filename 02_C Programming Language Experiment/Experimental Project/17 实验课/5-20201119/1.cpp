#include<stdio.h> 
#include<math.h> 
#include<string.h>

int main(void)
{
	int m,n,flag,count=0;
	scanf("%d",&m);
	int a[50];
	if(m>=0)//判断正负，如果是正数不变，如果是负数则根据二进制原理加上相应值 
		n=m;
	else
		n=m+(int)pow(2,32)+1;	
	for(int j=0;j<32;j++)//采用除二取余法依次将二进制从低位到高位存入数组 
	{
		flag=n%2;
		n=(int)(n/2);
		count++;
		a[j]=flag;
	} 
	if(m<0)//如果小于零，则把符号位置为1 
		a[31]=1;
	for(int j=count-1;j>=0;j--)//从高位到低位输出二进制 
	{
		if(j!=0&&(j+1)%4==0&&(j+1)!=32)
			printf(" ");//实现按格式输出 
		printf("%d",a[j]);
	}
		
	printf("\n");
	return 0;
}
