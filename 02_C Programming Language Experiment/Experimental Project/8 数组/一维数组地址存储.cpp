#include<stdio.h>
int main(void)
{
	int num=1;
	char value[4]={'7','8','9','6'};
	int number[]={5,8};
	printf("number:     0x%x\n",number);
	printf("number[0]:  0x%x\n",&number[0]);
	printf("number[1]:  0x%x\n",&number[1]);
	printf("value[-1]:  0x%x\n",&value[-1]);
	printf("value[0]:   0x%x\n",&value[0]);
	printf("value[1]:   0x%x\n",&value[1]);
	printf("value[2]:   0x%x\n",&value[2]);
	printf("value[3]:   0x%x\n",&value[3]);
	printf("value:      0x%x\n",value);
	printf("value:      0x%x\n",&value);
	printf("num:        0x%x\n",&num);
} 
