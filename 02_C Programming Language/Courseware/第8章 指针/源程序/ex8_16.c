#include "stdio.h"
#define I 2
#define J 3
#define K 4
void main(void)
{
	  int v[I][J][K],*p,n=1;
	  int i,j,k;
	  p=&v[0][0][0];       /* ʹpָ����ά����v�Ĵ�ͷ�Ļ���Ԫ�� */ 
	  for(i=0;i<I;i++)
		  for(j=0;j<J;j++)
			for(k=0;k<K;k++)
				*(p+i*J*K+j*K+k)=n++;      /* ��������v��v[i][j][k]Ԫ��*/
	  for(i=0;i<I;i++){
		for(j=0;j<J;j++){
			for(k=0;k<K;k++)
				printf("%4d",*(v[i][j]+k));/*v[i][j]+kҲ��ָ�����Ԫ�ص�ָ��*/
			printf("\n");
		  }
		  printf("\n");
	  }
}
