#include<stdio.h>
#include<string.h>
#define N 10000
char res[N];
char *re_add(int n,char *s);
int judge(char *s);
int main(void)
{
	int n;
	scanf("%d",&n);
	char num[N],*p=num;
	scanf("%s",num);
	for(int i=0;i<30;i++)
	{
		if(judge(p)) {printf("STEP=%d",i);return 0;}
		p=re_add(n,p);
		
	}
	printf("Impossible!");
}

char *re_add(int n,char *str1)
{
	//将传递的str1反转得到str2 
	char str2[N];
	int len=strlen(str1),i=0,ans=0,flag=1;
	for(;i<len;i++)
		str2[i]=str1[len-1-i];
	str2[len]='\0';
	int s1[N]={0},s2[N]={0},result[N]={0};
	
	len=(strlen(str1)>strlen(str2))?strlen(str1):strlen(str2);
	//将字符串转换为数字进行高精度加法 
	for(int i=strlen(str1)-1,j=0;i>=0;i--,j++)
	{
		if(str1[i]<='9'&&str1[i]>='0') s1[j]=str1[i]-'0';
		else s1[j]=str1[i]-'A'+10;
	}
	for(int i=strlen(str2)-1,j=0;i>=0;i--,j++)
	{
		if(str2[i]<='9'&&str2[i]>='0') s2[j]=str2[i]-'0';
		else s2[j]=str2[i]-'A'+10;
	}
	for(int i=0;i<=len+1;i++)
	{
		result[i]=s1[i]+s2[i]+ans;
		if(result[i]>=n) {ans=result[i]/n;result[i]%=n;}
		else ans=0;
	}
	//将整型数组result转换为字符数组res 
	for(int i=len+1;i>=0;i--){
		if(flag&&result[i]==0) continue;
		flag=0;
		char c;
		if(result[i]>=10)	c=result[i]-10+'A';
		else				c=result[i]+'0';
		res[i]=c;
	}
	return res;
}

int judge(char *s)
{
	for(int i=0;i<strlen(s);i++)
		if(s[i]!=s[strlen(s)-1-i]) return 0; 
	return 1;
}
