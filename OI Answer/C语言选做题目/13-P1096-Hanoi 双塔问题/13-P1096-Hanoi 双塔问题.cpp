#include<stdio.h>
#include<string.h>
#define N 2000
void multi_long(char*str1,char*str2);
char *step;
void reverse(char *s);
int main(void)
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		if(i==1) multi_long("2","2");
		else multi_long(step,"2");
	}
	step[strlen(step)-1]-=2;
	printf("%s",step);
}
void multi_long(char*str1,char*str2)
{
	int s1[N]={0},s2[N]={0},result[N]={0};
	char res[N];
	int len1=strlen(str1),len2=strlen(str2),len=len1+len2;
	for(int i=0;i<len1;i++)
		s1[i]=str1[len1-i-1]-'0';
	for(int i=0;i<len2;i++)
		s2[i]=str2[len2-i-1]-'0';
	for(int i=0;i<len1;i++)
		for(int j=0;j<=len2;j++)
		{
			result[i+j]+=+s1[i]*s2[j];
			result[i+j+1]+=result[i+j]/10;
            result[i+j]=result[i+j]%10;
		}
	while(result[len-1]==0&&len>1) len--;
	for(int i=0;i<=len-1;i++) 
		res[i]=result[i]+'0';
	res[len]='\0';
	reverse(res);
	step=res;
}
void reverse(char *s)
{
	int c,j,k;
	for(j=0,k=strlen(s)-1;j<k;j++,k--)
		c=s[j],s[j]=s[k],s[k]=c;
}
