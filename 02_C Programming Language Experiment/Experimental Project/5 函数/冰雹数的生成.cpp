#include<stdio.h>
#include<time.h>
#include<stdlib.h> 
int hailstone(int n) 
{
	printf("Hailstone generated by %d:\n",n);
	int count=1;
	int m;
	m=n;
	printf("%4d",n);
	while(m!=1){
	if(m%2){
		m=3*m+1;
		count++;
			if((count-1)%6==0)
			printf("%4d",m);
			else
			printf("%5d",m);
	}
	else
		{
			m=m/2;
			count++;
			if((count-1)%6==0)
			printf("%4d",m);
			else
			printf("%5d",m);
		}
	if(count%6==0)
		printf(" \n");
	}
	printf("\nNumber of hailstone generated:%d",count);
}
int main(void)
{
	int n;
	scanf("%d",&n);
	hailstone(n);
	return 0;
} 
