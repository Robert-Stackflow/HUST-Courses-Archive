#include<string.h>
#include<stdio.h> 
int fun(int a)
{
	int b[8];
	for(int i=0;i<8;i++)
	{
		b[i]=a%2;
		a=a/2;
	}
	for(int j=0;j<5;j=j+2){
		int q=b[j];
		b[j]=b[j+1];
		b[j+1]=q;
	}
 	int p=b[6]+b[7]*2,s=0;
 	for(int i=0,r=1;i<6;i++,r=r*2)
 	{
	 s=s+b[i]*r;
	}	
 	s=((s<<p)|(s>>(6-p)))&63;
 	s+=p<<6;
 	
	return s;
}
int main()
{
	char a[100],b[100];
	gets(a);
	int i=0;
	for(;i<strlen(a);++i){
	   	b[i]=(char)fun((int)a[i]);
	   	printf("%c",b[i]);
		}
	return 0;
}
