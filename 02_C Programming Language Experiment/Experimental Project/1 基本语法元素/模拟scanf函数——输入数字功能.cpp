#include<stdio.h> 
int main(void)
{
	char c;
	int x;
	for(x=0,c=getchar();c>='0'&&c<='9';c=getchar())
		x=10*x+c-'0';
	//*10ʱ���ý�λ�ƣ�������������-��0���Ǽ�ȥASCII�� 
	printf("x=%d\n",x);
	return 0; 
}
