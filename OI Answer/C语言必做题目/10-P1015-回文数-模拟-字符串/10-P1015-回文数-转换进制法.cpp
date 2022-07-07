#include<stdio.h>
#include<math.h>
//说明：该方法在洛谷上的AC率很低，仅仅有25%，是存在有漏洞的
//该问题存在的根本漏洞是我们要判断的是这个字符串相加之后的是否为回文串
//而不是其转换为十进制数后这个十进制数是不是回文数
//要搞清楚问题的本质，因此要用到任意进制的高精度加法运算 
//例如对于测试组16 adfd，正确答案为STEP=2；
//例如对于测试组16 AC27，正确答案为STEP=6；
//而该方法对于以上两个测试机的输出结果均为3 
int change(int n);
int transform(int base,char*str);
int judge(int n);
int main(void)
{
	int n,m,flag=0;
	char str[100];
	scanf("%d%s",&n,str);
	m=transform(n,str);//将字符串转换为对应的十进制数字
	printf("%d",m); 
	for(int i=0;i<30;i++)
	{
		if(judge(m)) {printf("STEP=%d",i);return 0;}
		m+=change(m);
	}
	printf("Impossible!");
}

int change(int n)
{
	int n1=0;
	for(int i=0;;i++)
	{
		n1=n1*10+n%10;
		n/=10;
		if(n==0) break;
	} 
	return n1;
}//将一个数字反转 
int judge(int n)
{
	int flag=0;
	if(change(n)==n) flag=1;
	return flag;			
}//判断是否为回文数 
int transform(int base,char*str)
{
	int j=0,num=0;
	for(;str[j]!='\0';j++)
	{
		if(str[j]>='0'&&str[j]<='9') num=num*base+str[j]-'0';
		if(str[j]>='a'&&str[j]<='f') num=num*base+str[j]-'a'+10;
		if(str[j]>='A'&&str[j]<='F') num=num*base+str[j]-'A'+10;
	}
	return num;
}
