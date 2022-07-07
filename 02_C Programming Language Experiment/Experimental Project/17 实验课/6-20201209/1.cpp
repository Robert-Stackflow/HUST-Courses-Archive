#include<stdio.h> 
int main(void)
{
	long int num;
	scanf("%ld",&num);
	unsigned char *p=(unsigned char *)&num;
	for(int i=3;i>=0;i--)
	{
		printf("%x %x",(*(p+i))>>4,(*(p+i))&15);
		if(i>0)	printf(" ");
	}
	return 0;
}
