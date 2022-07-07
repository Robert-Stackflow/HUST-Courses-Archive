#include<stdio.h> 
//判断字符串是否均为数字的函数 
int Tel(char num[])
{
	int i=0;
	for(;;i++)
	{
	if(num[i]>='0'&&num[i]<='9')
	return 1;
	else 
	return 0; 
	}
}
//计算字符串的长度的函数 
int length(char num[])
{
	int i=0;
	while(num[i]!='\0')
	++i;
	return i; 
}
int main(void)
{
	int j=0;
	char c;
	char num[1000];
	while(scanf("%s",num)!=EOF)
	{
	if (Tel(num))
	{
		if(length(num)==11)
		{
			if (num[0]!='1')
				printf("第1位不合法！\n");
			else{
				if(num[1]!='3'&&num[1]!='4'&&num[1]!='5'&&num[1]!='7'&&num[1]!='8')
					printf("第2位不合法！\n");
				else
					printf("该手机号合法！\n"); 
				} 
		}
		else
			printf("长度不合法！\n");
	}
	else
		printf("您输入了非数字字符！\n");
	} 
	return 0;
}
