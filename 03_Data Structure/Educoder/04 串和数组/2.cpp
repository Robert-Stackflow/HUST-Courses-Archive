#include "stdio.h"
#define  MAXSIZE 10000
typedef int ElemType;
typedef struct  {
   int       i,j;//非零元行、列下标
   ElemType    e;
 } Triple;        //三元组定义

typedef struct  {
   Triple  data[MAXSIZE+1];   //三元组从下标1开始存放
   int  mu,nu,tu;         //对于矩阵的行数、列数和非零元素值
 } TSMatrix;              //三元组顺序表的定义
TSMatrix ADD(TSMatrix M,TSMatrix N);
int main()
{
   TSMatrix A[3],B,C;
   int i,j;
   for(i=0;i<2;i++)
   {
   		scanf("%d%d%d",&A[i].mu,&A[i].nu,&A[i].tu);
   		for(j=1;j<=A[i].tu;j++)
   		 	scanf("%d%d%d",&A[i].data[j].i,&A[i].data[j].j,&A[i].data[j].e);
   }
   A[2]=ADD(A[0],A[1]);
   printf("%d %d %d\n",A[2].mu,A[2].nu,A[2].tu);
   for(i=1;i<=A[2].tu;i++)
   		printf("%d %d %d     ",A[2].data[i].i,A[2].data[i].j,A[2].data[i].e);
	return 1;
}
TSMatrix ADD(TSMatrix M,TSMatrix N)
{
/************** begin *****************/
    TSMatrix Q;
    int m,n,k;
    Q.mu=M.mu;
    Q.nu=M.nu;
    Q.tu=0;
    m=n=k=1;
    while(m<=M.tu&&n<=N.tu)
	{
        if(M.data[m].i<N.data[n].i)
		{
            Q.data[k].i=M.data[m].i;
            Q.data[k].j=M.data[m].j;
            Q.data[k].e=M.data[m].e;
            m++;
        }//m的行坐标小
		else if(M.data[m].i>N.data[n].i)
		{
            Q.data[k].i=N.data[n].i;
            Q.data[k].j=N.data[n].j;
            Q.data[k].e=N.data[n].e;
            n++;
        }//n的行坐标小
		else
		{
            if(M.data[m].j<N.data[n].j)
			{
                Q.data[k].i=M.data[m].i;
                Q.data[k].j=M.data[m].j;
                Q.data[k].e=M.data[m].e;
                m++;
            }
			else if(M.data[m].j>N.data[n].j)
			{
                Q.data[k].i=N.data[n].i;
                Q.data[k].j=N.data[n].j;
                Q.data[k].e=N.data[n].e;
                n++;
            }
			else
			{
                if((M.data[m].e+N.data[n].e)==0)
				{
                    m++;
                    n++;
                    continue;
                }
				else
				{
                    Q.data[k].i=M.data[m].i;
                    Q.data[k].j=M.data[m].j;
                    Q.data[k].e=M.data[m].e+N.data[n].e;
                    m++;
                    n++;
                }
            }
        }//m,n的行坐标相同
        k++;
        Q.tu++;
    }
    while(m<=M.tu)
	{
        Q.data[k]=M.data[m];
        m++;
        k++;
        Q.tu++;
    }
    while(n<=N.tu)
	{
        Q.data[k]=N.data[n];
        n++;
        k++;
        Q.tu++;
    }
    return Q;
/**************  end  *****************/
}
