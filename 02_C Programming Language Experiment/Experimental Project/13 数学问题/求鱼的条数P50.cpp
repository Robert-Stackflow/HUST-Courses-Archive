#include<stdio.h>
#include<stdbool.h>
int main(void)
{ 
	int n,i,x;
	bool flag=true;
	for (n=6;flag;n++)
	{
		for(x=n,i=1;flag&&i<=5;i++){
			if((x-1)%5==0)
			x=4*(x-1)/5;
			else flag=false;
		}
		if(flag) break;
		else flag=true;
  	}
	printf("Total number of fish catched=%d\n",n);
	return 0;
}
