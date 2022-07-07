#include<stdio.h>
#include<string.h>
#define max(m,n) (((m)>(n))?(m):(n)) 
#define N 1000
char* add_long(char*str1,char*str2,char*res,int base); 
int main(void)
{
	int n;
	scanf("%d",&n);
	char str1[N],str2[N],res[N];
	scanf("%s%s",str1,str2);
	printf("%s",add_long(str1,str2,res,n));
}

char* add_long(char*str1,char*str2,char*res,int base)
{
	int s1[N]={0},s2[N]={0},result[N]={0},ans=0,flag=1;
	int len=max(strlen(str1),strlen(str2));
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
		if(result[i]>=base) {ans=result[i]/base;result[i]%=base;}
		else ans=0;
	}
	for(int i=len+1;i>=0;i--){
		if(flag&&result[i]==0) continue;
		flag=0;
		char c;
		if(result[i]>=10)	c=result[i]-10+'a';
		else				c=result[i]+'0';
		res[i]=c;
	}
	res[len+1]='\0';
	strrev(res);
	return res;
}
