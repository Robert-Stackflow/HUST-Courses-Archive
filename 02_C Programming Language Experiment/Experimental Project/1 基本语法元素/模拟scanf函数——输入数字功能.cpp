#include<stdio.h> 
int main(void)
{
	char c;
	int x;
	for(x=0,c=getchar();c>='0'&&c<='9';c=getchar())
		x=10*x+c-'0';
	//*10时采用进位制，依次输入数字-‘0’是减去ASCII码 
	printf("x=%d\n",x);
	return 0; 
}
