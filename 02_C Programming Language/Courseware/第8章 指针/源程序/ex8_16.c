#include "stdio.h"
#define I 2
#define J 3
#define K 4
void main(void)
{
	  int v[I][J][K],*p,n=1;
	  int i,j,k;
	  p=&v[0][0][0];       /* 使p指向三维数组v的打头的基本元素 */ 
	  for(i=0;i<I;i++)
		  for(j=0;j<J;j++)
			for(k=0;k<K;k++)
				*(p+i*J*K+j*K+k)=n++;      /* 访问数组v的v[i][j][k]元素*/
	  for(i=0;i<I;i++){
		for(j=0;j<J;j++){
			for(k=0;k<K;k++)
				printf("%4d",*(v[i][j]+k));/*v[i][j]+k也是指向基本元素的指针*/
			printf("\n");
		  }
		  printf("\n");
	  }
}
