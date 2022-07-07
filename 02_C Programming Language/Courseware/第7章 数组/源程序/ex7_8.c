#include "stdio.h"
#define SIZE 3
int main(void)
{	int x[SIZE]={1,3,5},k;
	printf("the value of x is 0x%x\n",x);
	for(k=0;k<SIZE;k++)
		printf("k=%d\tx[%d]=%d\taddr=0x%x\n",k,k,x[k],&x[k]);
	return 0;
}
