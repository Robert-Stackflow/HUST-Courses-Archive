#include<stdio.h> 
#define m 3000
int main(void)
{
	
	int i=1;
	float Sn;
	for(;i<=m;++i){
	Sn+=(float)1/(i*i*i);
	}	
	printf("%.7f",Sn);
	return 0;
}
