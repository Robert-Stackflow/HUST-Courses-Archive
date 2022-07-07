#include<stdio.h>
#include<stdlib.h>
#define PI 3.14159
int main(void)
{
	int f;
	short p,k;
	double c,r,s;
	
	printf("Input Fahrenheit:");
	scanf("%d",&f);
	c=(float)5/9*(f-32);
	printf("\n%d(F)=%.2f(C)\n\n",f,c);
	
	printf("Input the radius r:");
	scanf("%lf",&r);
	s=r*r*PI;
	printf("\nThe acreage is %.2f\n\n",s);
	
	short newint; 
	k=0xa1b2,p=0x8423;
	newint=p&0xff00|(((k&0xff00)>>8)&0x00ff);
	printf("new int=%hx\n\n",newint);
	return 0;
	
 } 
