#include<stdio.h>
int main(void)
{
	char *names[4]=
	{
		"hello",
		"cs2020",
		"jjj",
		"lk"
	};
	for(int i=0;i<4;i++)
	{
		printf("names[%d]=%s\n",i,names[i]);
		printf("&names[%d]=%p\n",i,names[i]);
	}
}
