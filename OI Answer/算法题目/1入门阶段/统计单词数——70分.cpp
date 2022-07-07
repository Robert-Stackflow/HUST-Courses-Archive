#include<stdio.h>
#include<string.h>
int judge(char ch1,char ch2)
{
	if((ch1==ch2)||(ch1==ch2-32)||(ch1==ch2+32)) return 1;
	else return 0;
}
int i,j,k,start=-1,ans,cmd=1;
int main(void)
{
    char check[11],s[1000002];
	gets(check);
	gets(s);
//	puts(s);
	for(;i<strlen(s);i++)
	{
	if(i==0||(s[i]==' '&&judge(s[i+1],check[0])&&judge(s[i+2],check[1])))
	{
		int k=i;
		j=0;
		cmd=1;
		if(s[k]==' ') k++;
		while(cmd)
		{
		if(judge(check[j],s[k]))
		{
		k++;
		j++;
		if(j==strlen(check)) cmd=0;
		if(j==strlen(check)&&(s[k]==' '||k==strlen(s)))
		{
			if(start==-1) start=k-strlen(check);
			ans++;
		}
		}
		else break;
		}
	}
	}
	if(ans==0) printf("-1");
	else printf("%d %d",ans,start);
	return 0;
}
