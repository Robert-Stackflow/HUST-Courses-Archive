#include<stdio.h>
#include<assert.h>
#define R  
int integer_fraction(float x);
int main(void)
{
	float r,s;
	int s_integer=0;
	printf("Tnput a number:");
	scanf("%f",&r);
	#ifdef R
		s=3.14159*r*r;
		s_integer=integer_fraction(s);
		
		assert((s-s_integer)<0.5);
		printf("The integer fraction of area is %d\n",s_integer);
	#endif
	return 0;
 } 
 
 int integer_fraction(float x)
 {
 	int i=x;
 	if((x-i)<0.5)
 		return i;
 	else 
	 	return i+1;
 }
 
