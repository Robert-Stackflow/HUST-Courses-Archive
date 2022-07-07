#include "stdio.h"
int main(void)
{	int x=12345,*p=&x,**pp=&p,***ppp=&pp;
	printf("&x=%p\tx=%d\n",&x,x);
	printf("&p=%p\tp=%d\n",&p,p);
	printf("&pp=%p\tpp=%d\n",&pp,pp);
	printf("&ppp=%p\tppp=%d\n",&ppp,ppp);
	return 0;
}
