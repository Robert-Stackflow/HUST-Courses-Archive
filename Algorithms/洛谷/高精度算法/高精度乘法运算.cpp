#include<stdio.h>
#include<string.h>
#define max(m,n) (((m)>(n))?(m):(n)) 
#define N 1000
char* multi_long(char*str1,char*str2,char*res); 
int main(void)
{
	char str1[N],str2[N],res[N];
	scanf("%s%s",str1,str2); 
	printf("%s",multi_long(str1,str2,res));
}

char* multi_long(char*str1,char*str2,char*res)
{
	int s1[N]={0},s2[N]={0},result[N]={0};
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
	strrev(res);
	return res;
}
