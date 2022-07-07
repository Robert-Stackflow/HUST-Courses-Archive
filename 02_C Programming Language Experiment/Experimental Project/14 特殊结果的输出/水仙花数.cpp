#include<stdio.h>
int main(void)
{
	int x,j,i,k,m=0;
	for(x=100;x<=999;++x){
		j=x/100;
		i=(x-j*100)/10;
		k=x%10;
		if (x==j*j*j+i*i*i+k*k*k){
			++m;
			printf("第%d个水仙花数是%5d  ;\n",m,x);
		}
		
	}
	return 0;
 } 
