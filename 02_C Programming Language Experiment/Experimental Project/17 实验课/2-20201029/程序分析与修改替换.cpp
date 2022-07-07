#include<stdio.h>
int main(void)
{
	int m,n,k=0,p,i,d;
	scanf("%d%d",&m,&n);
	if (m<n)
	{
		m = m ^ n;
		n = m ^ n;
		m = m ^ n;
	}
	while(((m&1)==0)&&((n&1)==0))
	{
		m>>1;
		n>>1;
		k++; 
	}
	for(p=1,i=0;i<k;i++)
		p=2<< (k-1);
	while((d=m-n)!=n){
		if(d>n)
		m=d;
		else
		n=(m=n,d); 
	}
	d*=p;
	printf("最大公约数是%d",d);
	return 0;
}
