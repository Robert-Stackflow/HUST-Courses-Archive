#include<stdio.h> 
int main(void)
{
	int x;
	char s[80]="��һ������������",c[]="����";
	scanf("%d",&x);
	if ((x>=1)&&(x<=7))
		c[2]=s[x];
		printf("%s",c);
		return 0;
}
