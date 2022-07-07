#include<stdio.h>
#include<math.h>
#include<string.h>
void conversion(char str[])
{
	long long sum=0;
	int flag=0,m=0,len;
	for(int i=0;i<strlen(str);i++)
	{
		if((str[i]>='A'&&str[i]<='F')||(str[i]>='a'&&str[i]<='f')||(str[i]>='0'&&str[i]<='9'))
			len++;
		else
			break;
	} 
	for(int i=0;i<strlen(str);i++)
	{
		if((str[i]>='A'&&str[i]<='F')||(str[i]>='a'&&str[i]<='f')||(str[i]>='0'&&str[i]<='9'))
		{
		if (str[i]>='a'&& str[i]<='f') 
        	str[i]=str[i]-32;
        if (str[i]>='0'&&str[i]<='9')
        {
        	flag=str[i]-48;
			sum+=flag*((int)pow(16,len-i-1));
		}
        else if(str[i]>='A'&&str[i]<='F')
        {
        	flag=str[i]-55;
			sum+=flag*((int)pow(16,len-i-1));
		}
		}
		else
			break;
	}
	printf("%d",sum);
}
int main(void)
{
	int sum;
	char str[100];
	int flag=0,m=0,len;
	while(scanf("%c",&str[m]),str[m]!='\n')
		m++;
	str[m]='\0';
	conversion(str);
	return 0;
}
