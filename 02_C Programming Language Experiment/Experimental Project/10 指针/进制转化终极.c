#include <stdio.h>
#include <math.h> 
#include <string.h> 
#define eps 1e-12
char s1[100000000],s2[100000000];
int i;
int toten(char x[],int n)
{
	int le,i,j,sum=0;
    le=strlen(x);
    
    for(i=le-1;i>=0;i--)
    {
    	if(x[i]>='0' && x[i]<='9')
		sum+=(x[i]-'0')*(int)pow(n,le-1-i);
		else
		sum+=(x[i]-'A'+10)*(int)pow(n,le-1-i);
	}
	
	return sum;
}

int tob(int x,int n)
{
	for(i=1;x>0;i++)
	{
		s2[i]=x%n;
		x/=n;
	    
	} 
}

int main()
{
	int a,b,j,x;
	
	scanf("%d%d",&a,&b);
	scanf("%s",s1);
	x=toten(s1,a);
	tob(x,b);
	for(j=i-1;j>0;j--)
	{
		if(s2[j]>=0  &&  s2[j]<=9)
		putchar(s2[j]+'0');
		else putchar(s2[j]-10+'A');
	}
	  
}
