#include "stdio.h"
#define I 3
#define J 3
#define K 3
int main(void)
{	int x[I][J][K],i=1,j=1,k=1,n=1;
	printf("%d\n",(*(x+i))[j][k]=n++);/*x[i]����(*(x+i))*/
	printf("%d\n",(*(*(x+i))+j)[k]=n++);/*x[i][j]����(*(*(x+i))+j)*/
	printf("%d\n",*(*(*(x+i)+j)+k)=n++);/*x[i][j][k]����*(*(*(x+i)+j)+k)*/
	printf("%d\n",*(x[i][j]+k)=n++);/*x[i][j]ΪE1,kΪE2*/
	printf("%d\n",*(*(x[i]+j)+k)=n++);/*��x[i][j]�ݹ�ʹ��E1[E2]�ȼ���*((E1)+(E2))*/
	printf("%d\n",*(*(*(x+i)+j)+k)=n++);/*��x[i]�ݹ�ʹ��E1[E2]�ȼ���*((E1)+(E2))*/
	return 0;
}
