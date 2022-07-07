#include<stdio.h>
int main(void)
{
	int x,i=1,Negative=0,Positive=0,Zero=0;
	printf("Input ten numbers£º");
	while (i<=10) {
	
	    scanf("%d",&x);
		(x>0?Positive++:(x<0?Negative++:Zero++)); 
		++i;
	}
	printf("In the ten numbers£¬there are %d positives£¬%d negatives,%d zero",Positive,Negative,Zero);
	return 0;
 } 
