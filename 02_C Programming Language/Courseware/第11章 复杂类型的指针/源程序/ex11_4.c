#include "stdio.h"
#define I 1
#define J 2
#define K 3
#define L 3
#define M 3
int main(void)
{
	  int s[I][J][K][L][M]; /* ������ά���� */
	  int (*p4)[J][K][L][M]=s; /* ����ָ����ά�����ָ�벢��ʼ�� */
	  int (*p3)[K][L][M]=s[0]; /* ����ָ����ά�����ָ�벢��ʼ�� */
	  int (*p2)[L][M]=s[0][0]; /* ����ָ���ά�����ָ�벢��ʼ�� */
	  int (*p1)[K]=s[0][0][0]; /* ����ָ��һά�����ָ�벢��ʼ�� */
	  int i,j,k,l,m,n=1;
	  for(i=0;i<I;i++)
		  for(j=0;j<J;j++)
			  for(k=0;k<K;k++)
				  for(l=0;l<L;l++)
					  for(m=0;m<M;m++){ 
						/* ��ָ��1ά�����ָ�������������Ԫ�� */
						  *(*(p1+l)+m+i*J*K*L*M+j*K*L*M+k*L*M)=n++;
			/* Ҳ��������������ָ��2ά���顢3ά���顢4ά�����ָ��ı��ʽ */
			/*  *(*(*(p2+k)+l)+m+i*J*K*L*M+j*K*L*M)=n++; */
			/*  *(*(*(*(p3+j)+k)+l)+m+i*J*K*L*M)=n++;*/
			/*  *(*(*(*(*(p4+i)+j)+k)+l)+m)=n++;*/
					}
	  for(i=0;i<I;i++)
		  for(j=0;j<J;j++)
			  for(k=0;k<K;k++){
				  for(l=0;l<L;l++){
					  for(m=0;m<M;m++)
						/* ��ָ��1ά�����ָ�������������Ԫ�� */
						  printf("%4d",*(*(p1+l)+m+i*J*K*L*M+j*K*L*M+k*L*M));
				/* Ҳ��������������ָ��2ά���顢3ά���顢4ά�����ָ��ı��ʽ */
				/* printf("%4d",*(*(*(p2+k)+l)+m+i*J*K*L*M+j*K*L*M));*/
				/* printf("%4d",*(*(*(*(p3+j)+k)+l)+m+i*J*K*L*M));  */
				/* printf("%4d",*(*(*(*(*(p4+i)+j)+k)+l)+m)); */
					printf("\n");
				}
		  		printf("\n");
	  		}
	  return 0;
}
