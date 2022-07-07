#include "stdio.h"
#include "stdlib.h"
#define I 2
#define J 3
#define K 4
int main(void)
{	int v[I][J][K],(*p)[J][K]=v,(*p1)[K]=v[0],n=1;/*p是指向下一级数组的指针*/
	int i,j,k;	/*上面的p1是指向下二级数组的指针*/
	for(i=0;i<I;i++)
		for(j=0;j<J;j++)
			for(k=0;k<K;k++)/* 用指向下二级数组的指针变量访问数组元素 */
				*(*(p1+j)+k+i*J*K)=n++;
	/* 也可以用*(*(*(p+i)+j)+k)=n++; 也可以用v[i][j][k]=n++; */
	for(i=0;i<I;i++){
		for(j=0;j<J;j++){ /* 用指向下一级数组的指针变量访问数组元素 */
			for(k=0;k<K;k++)
				printf("%4d",*(*(*(p+i)+j)+k));
			/* 也可以用printf("%d   ",*(*(p1+j)+k+i*J*K)); */
			/* 也可以用printf("%d  ",v[i][j][k]); */
				printf("\n");
		}
		printf("\n");
	}
	return 0;
}

