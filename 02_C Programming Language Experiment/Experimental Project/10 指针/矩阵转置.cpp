/*
写一函数，将一个3x3的整型矩阵转置，用指针实现
*/
#include <stdio.h>
#include <stdlib.h>
#define SIZE 3

int main()
{
　　int **a = (int **)malloc(sizeof(int *)*SIZE);//二维数组动态分配内存
　　int i,j,t;
　　for(i=0; i<SIZE; i++)
　　　　*(a+i) = (int *)malloc(sizeof(int)*SIZE);//二维数组动态分配内存

　　printf("请输入矩阵的元素：");
　　for(i=0; i<SIZE; i++)
　　for(j=0; j<SIZE; j++)
　　scanf("%d",*(a+i)+j);

　　for(i=0; i<SIZE; i++)//对矩阵进行转置
　　　　for(j=i; j<SIZE; j++)
　　　　{
　　　　　　t = *(*(a+i)+j);
　　　　　　*(*(a+i)+j) = *(*(a+j)+i);
　　　　　　*(*(a+j)+i) = t;
　　　　}

　　printf("转置之后为：");
　　for(i=0; i<SIZE; i++)
　　　　for(j=0; j<SIZE; j++)
　　　　　　printf("%d ",*(*(a+i)+j));
　　printf("\n");

　　return 0;
}
