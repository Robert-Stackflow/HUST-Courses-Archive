#include "stdio.h"
int main(void)
{
	int x=1,y=2,z=3,i;
	int *p[3];
	p[0]=&x;p[1]=&y;p[2]=&z;
	printf("&x=%p\tx=%d\n",&x,x);
	printf("&y=%p\ty=%d\n",&y,y);
	printf("&z=%p\tz=%d\n",&z,z);
	for(i=0;i<3;i++)
		printf("&p[%d]=%p\tp[%d]=%p\t*p[%d]=%d\n",i,&p[i],i,p[i],i,*p[i]);
	return 0;
}
