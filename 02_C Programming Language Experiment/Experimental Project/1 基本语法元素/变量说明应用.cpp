#include<stdio.h>
int main()
{
	int x=4,y=3,z=2;
	char c='a';
	if(c=='A'+32)
		printf("该式子1正确\n");
	else
	    printf("该式子1不正确\n");
	if(c+1!='b') 
		printf("该式子2正确\n");
	else
	    printf("该式子2不正确\n");
	if(x-y<=10)
		printf("该式子3正确\n");
	else
	    printf("该式子3不正确\n");
	if(z=x>y)
		printf("该式子4正确\n");
	else
	    printf("该式子4不正确\n");
	if(x>y>z)
		printf("该式子5正确\n");
	else
	    printf("该式子5不正确\n");
	return 0;
 } 
