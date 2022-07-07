#include "stdio.h"
#define N 3
#define K 4
#define M 3
void mul_matrix(int a[][K],int b[][M],int C[][M],int n,int k,int m);
int main(void)
{
	  int A[N][K]={{1,2,3,4},{5,6,7,8},{9,0,1,2}};
	  int B[K][M]={{1,2,3},{4,5,6},{7,8,9},{0,1,2}};
	  int C[N][M];
	  int i,j;
	  mul_matrix(A,B,C,N,K,M);
	  for(i=0;i<N;i++){
		  for(j=0;j<M;j++)
			  printf("%8d  ",C[i][j]);
		  printf("\n");
	  }
	  return 0;
}
void mul_matrix(int a[][K],int b[][M],int c[][M],int n,int k,int m)
{
	  int i,j,p,sum;
	  for(i=0;i<n;i++)
		  for(j=0;j<m;j++){
			  sum=0;
			  for(p=0;p<k;p++)
				  sum+=a[i][p]*b[p][j];
			  c[i][j]=sum;
		  }
}
