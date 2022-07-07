#include<stdio.h>
#include<string.h>
/*样例输入
666666666666666666666666666666666666666666666666666666666666666666
22222222222222222222222222222222222222222222222222222222222222222
*/ 
//1、一个m位的整数与一个n位的整数相乘，乘积为m+n-1位或m+n位。
//2、程序中，用三个字符数组分别存储乘数、被乘数与乘积。由第1点分析知，存放乘积的字符数组的长度应不小于存放乘数与被乘数的两个数组的长度之和。
//3、可以把第二步“计算填表”与第三四步“累加进位”放在一起完成，可以节省存储表格2所需的空间。
//4、程序关键部分是两层循环，内层循环累计一组数的和，外层循环处理保留的数字与进位。
void store(int s[],char*str);
int main()
{
	int num1[200],num2[200],c[200]={0};
	char str1[200],str2[200];
	scanf("%s",str1);
	scanf("%s",str2);
	store(num1,str1);
	store(num2,str2);
	printf("长度1：%d\n",num1[0]);
	printf("长度2：%d\n",num2[0]);
	for(int i=1;i<=num1[0];i++)
	{
	//作按位乘法并处理进位，此处是万进制进位
	for(int j=1;j<=num2[0];j++)
	{
	c[i+j-1]+=num1[i]*num2[j];
	c[i+j]+=c[i+j-1]/10000;
	c[i+j-1]%=10000;
	}
	} 
	int len=num1[0]+num2[0];//a[0]和b[0]存放的是每个数按4位处理的位数
	while ((c[len]==0)&&(len>1)) len--;//去掉高位的0，并输出最高位
	for(int i=len;i>=1;i--)//把剩下来的每一位还原成4位输出
	{
	if(i==1)
	{
	if (c[i]<1000) printf("0");
	if (c[i]<100) printf("0");
	if (c[i]<10) printf("0");	
	}
	printf("%d",c[i]);
	}
	return 0;
}
void store(int s[],char*str)
{   
	int k=1,count=1;
	s[0]=strlen(str);
	for(int i=s[0]-1;i>=0;i--)
	{ 
	if (count%4==0)
	{
	s[k]+=(str[i]-'0')*1000;
	if(i!=0) k++;
	}
	if (count%4==1) s[k]=(str[i]-'0');
	if (count%4==2) s[k]+=(str[i]-'0')*10;
	if (count%4==3) s[k]+=(str[i]-'0')*100;
	count++;
	}
	s[0]=k;
	printf("长度：%d\n",s[0]);
}
