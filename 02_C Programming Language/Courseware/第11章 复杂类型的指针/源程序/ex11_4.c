#include "stdio.h"
#define I 1
#define J 2
#define K 3
#define L 3
#define M 3
int main(void)
{
	  int s[I][J][K][L][M]; /* 声明五维数组 */
	  int (*p4)[J][K][L][M]=s; /* 声明指向四维数组的指针并初始化 */
	  int (*p3)[K][L][M]=s[0]; /* 声明指向三维数组的指针并初始化 */
	  int (*p2)[L][M]=s[0][0]; /* 声明指向二维数组的指针并初始化 */
	  int (*p1)[K]=s[0][0][0]; /* 声明指向一维数组的指针并初始化 */
	  int i,j,k,l,m,n=1;
	  for(i=0;i<I;i++)
		  for(j=0;j<J;j++)
			  for(k=0;k<K;k++)
				  for(l=0;l<L;l++)
					  for(m=0;m<M;m++){ 
						/* 用指向1维数组的指针变量访问数组元素 */
						  *(*(p1+l)+m+i*J*K*L*M+j*K*L*M+k*L*M)=n++;
			/* 也可以用下面声明指向2维数组、3维数组、4维数组的指针的表达式 */
			/*  *(*(*(p2+k)+l)+m+i*J*K*L*M+j*K*L*M)=n++; */
			/*  *(*(*(*(p3+j)+k)+l)+m+i*J*K*L*M)=n++;*/
			/*  *(*(*(*(*(p4+i)+j)+k)+l)+m)=n++;*/
					}
	  for(i=0;i<I;i++)
		  for(j=0;j<J;j++)
			  for(k=0;k<K;k++){
				  for(l=0;l<L;l++){
					  for(m=0;m<M;m++)
						/* 用指向1维数组的指针变量访问数组元素 */
						  printf("%4d",*(*(p1+l)+m+i*J*K*L*M+j*K*L*M+k*L*M));
				/* 也可以用下面声明指向2维数组、3维数组、4维数组的指针的表达式 */
				/* printf("%4d",*(*(*(p2+k)+l)+m+i*J*K*L*M+j*K*L*M));*/
				/* printf("%4d",*(*(*(*(p3+j)+k)+l)+m+i*J*K*L*M));  */
				/* printf("%4d",*(*(*(*(*(p4+i)+j)+k)+l)+m)); */
					printf("\n");
				}
		  		printf("\n");
	  		}
	  return 0;
}
