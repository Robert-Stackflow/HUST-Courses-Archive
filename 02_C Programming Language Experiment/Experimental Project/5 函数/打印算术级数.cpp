#include<stdio.h>
#define LIMIT 5
int display(int a,int d);
int display_concrete(int a,int d,int k);  
int main()
{
	int a,d;
	int k;
	printf("Input the first item and the differential:");
	scanf("%d%d",&a,&d);
	printf("Now we will display the first hundred terms:\n");
	display(a,d);
	printf("\nInput a number you want to get:");
	scanf("%d",&k);
	display_concrete(a,d,k);
}
int display(int a,int d)
{
	for(int i=1;i<=100;i++)
	{
		printf("%d\t",a+(i-1)*d);
		if(i%LIMIT==0)printf("\n");
	}
		
}
int display_concrete(int a,int d,int k)
{
	printf("The number you want is %d\n",a+(k-1)*d);
}
