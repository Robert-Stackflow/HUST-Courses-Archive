#include<stdio.h>
int main()
{
	char a[100];
	char d[100];
	gets(a);
	unsigned short  b[100];
	int i;
	b[i]=a[i];      
	for(i=0;a[i]!='\0';i++)
	{
	int c[8],m=0;      
	for(m=0;m<=7;m++)
	{
		c[m]=b[i]%2;
		b[i]=b[i]/2;            
	}
	if(m%2==0)
	{
		c[m]=c[m]^c[m+1];
		c[m+1]=c[m]^c[m+1];
		c[m]=c[m]^c[m+1];
	}
	int n;
	char e[8];
	n=c[6]+c[7]*2;
	if(m<=5&&(m+n)<=5)
	{
		e[m]=c[m+n];
	}
	else if(m<=5&&(m+n)>5)
	{
		e[m]=c[m+n-6];
	}
	e[6]=c[6];
	e[7]=c[7];
	int t=0,y=1;
	m=0;
	t+=e[0];
	while(m<=7)
	{
		m+=1;
		y*=2;
		t=t+e[m]*y;
	}
	d[i]='t';
	}
	printf("%s",d);
	return 0;
	
	
}

