#include<stdio.h>
#include<string.h>
#define N 1000
//该题的实质是高精度加法
//注意不要忽略进位导致的数组长度扩大，从而少输出位次 
int main(void)
{
	int n,ans=0,flag=1;
	scanf("%d",&n);
	char str1[N],str2[N],res[N];
	int s1[N]={0},s2[N]={0},result[N]={0};
	scanf("%s%s",str1,str2);
	int len=(strlen(str1)>strlen(str2))?strlen(str1):strlen(str2);
	for(int i=strlen(str1)-1,j=0;i>=0;i--,j++)
	{
		if(str1[i]<='9'&&str1[i]>='0') s1[j]=str1[i]-'0';
		else s1[j]=str1[i]-'a'+10;
	}
	for(int i=strlen(str2)-1,j=0;i>=0;i--,j++)
	{
		if(str2[i]<='9'&&str2[i]>='0') s2[j]=str2[i]-'0';
		else s2[j]=str2[i]-'a'+10;
	}
	for(int i=0;i<len+1;i++)
	{
		result[i]=s1[i]+s2[i]+ans;
		if(result[i]>=n) {ans=result[i]/n;result[i]%=n;}
		else ans=0;
	}
	for(int i=len;i>=0;i--){
		if(flag&&result[i]==0) continue;
		flag=0;
		char c;
		if(result[i]>=10)	c=result[i]-10+'a';
		else				c=result[i]+'0';
		printf("%c",c);
	}
}

