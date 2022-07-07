#include<stdio.h> 
#include<string.h>
int angle(int z)
{
	int n[8];
	int i=0; 
	for(;i<=7;++i)
	{
		n[i]=z%2;
		z/=2;
	}
	int j=0;
	for(;j<=4;j+=2)
	{
		int p=n[j];
		n[j]=n[j+1];
		n[j+1]=p;
	}
 	int k=n[6]+n[7]*2;
 	int t=0;
 	for(int i=0,r=1;i<=5;++i,r*=2)
 		t+=n[i]*r;
 	t=((t<<k)|(t>>(6-k)))&63;
 	t+=k<<6;
 	return t;
}
int main()
{
	char m[100],z[100];
	gets(m);
	for(int i=0;i<=strlen(m)-1;i++)
	   	{
	   		z[i]=(char)angle((int)m[i]);
	   		printf("%c",z[i]);
		}
	return 0;
}
