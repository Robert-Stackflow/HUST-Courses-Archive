#include<stdio.h>
#include<stdlib.h>
typedef int ElemType;
void ShiftRightCircular(ElemType *A,int n,int k);
int main()
{
    int n,i,k;
    ElemType *p;
    scanf("%d%d",&n,&k);
    p=(int *)malloc(n*sizeof(int));
    for(i=0;i<n;i++)
        p[i]=i+1;
	for(i=0;i<n;i++)
        printf(" %d",p[i]);
        printf("\n");
    ShiftRightCircular(p,n,k);
    for(i=0;i<n;i++)
        printf(" %d",p[i]);
    return 1;
}

void ShiftRightCircular(ElemType *A,int n,int k)
{
/************** begin *****************/
	ElemType e1;
	if(k<0) k=n+(k%10);
	k%=10;
	for(int i=0;i<n/2;i++){
        e1=A[i];
        A[i]=A[n-i-1];
		A[n-i-1]=e1;
    }
	for(int i=0;i<k/2;i++){
        e1=A[i];
        A[i]=A[k-i-1];
		A[k-i-1]=e1;
    }
    for(int i=0;i<(n-k)/2;i++){
        e1=A[k+i];
        A[k+i]=A[n-i-1];
		A[n-i-1]=e1;
    }
/**************  end  *****************/
}
