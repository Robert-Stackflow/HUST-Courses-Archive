#include<stdio.h> 
int main(void)
{
	int number,x,y,z;
	printf("������һ����λ����"); 
	scanf("%d",&number);
	z=number/100;
	y=number/10%10;
	x=number%10;
	if(y>x&&y>z)
		printf("����һ��ɡ��\n") ;
	else
		printf("�ⲻ��һ��ɡ��\n") ;
	return 0;
}
