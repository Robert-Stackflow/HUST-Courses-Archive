#include<stdio.h>
#include<stdlib.h>
int main(void)
{
	int k,n;
	double s=0;
	scanf("%d",&k);
	for(int i=1;;i++)
	{
		s+=1.0/i;
		if(s>k) {printf("%d",i);break;}
	}
	return 0;
}
