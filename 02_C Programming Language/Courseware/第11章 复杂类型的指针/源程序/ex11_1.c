#include "stdio.h"
#define I 3
#define J 3
#define K 3
int main(void)
{	int x[I][J][K],i=1,j=1,k=1,n=1;
	printf("%d\n",(*(x+i))[j][k]=n++);/*x[i]等于(*(x+i))*/
	printf("%d\n",(*(*(x+i))+j)[k]=n++);/*x[i][j]等于(*(*(x+i))+j)*/
	printf("%d\n",*(*(*(x+i)+j)+k)=n++);/*x[i][j][k]等于*(*(*(x+i)+j)+k)*/
	printf("%d\n",*(x[i][j]+k)=n++);/*x[i][j]为E1,k为E2*/
	printf("%d\n",*(*(x[i]+j)+k)=n++);/*对x[i][j]递归使用E1[E2]等价于*((E1)+(E2))*/
	printf("%d\n",*(*(*(x+i)+j)+k)=n++);/*对x[i]递归使用E1[E2]等价于*((E1)+(E2))*/
	return 0;
}
