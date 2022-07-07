#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define N 10   /* 需要排序的数组元素的数量 */

void CreateData(int a[ ],int n,int low,int high) ; /* 生成随机数的函数原形 */
void InsertSort(int a[], int n) ;  /* 直接插入排序的函数原形 */

int main()
{
	int i,data[N];
	CreateData(data,N,100,999);  /* 生成随机数*/
	printf("排序前：");
	for(i=0;i<N;i++)   /* 输出生成的随机数 */
		printf("%d  ",data[i]);
	InsertSort(data, N);   /* 调用直接插入排序函数 */
	printf("\n排序后：");
	for(i=0;i<N;i++)      /* 输出排序后的结果 */
		printf("%d  ",data[i]);
	printf("\n");
	return 0;
}
/***********************************************************************
　CreateData函数功能：产生若干的随机整数。
　函数参数：a是保存生成数据的数组，n是元素个数，min是数据的最小值，max是数据的最大值
************************************************************************/ 
void CreateData(int a[ ],int n,int low,int high) 
{     
	int i,k; 
    double d;
	srand(time(NULL));  /* 用系统时间初始化随机数发生器 */ 
    for (i=0; i<n; i++)
	{   /*将rand库函数产生的值限制为0≤d<1  */            
		d=(double)rand()/((double) RAND_MAX+1); 
        k = (int)(d*(high-low+1));  /* 将d的值按照需要的范围扩大并取整 */
        a[i]=k+low;  /* 从需要的最小值开始 */
	}
}

/***********************************************************************
  InsertSort函数功能：直接插入排序算法,对n个整数递增排序。
　函数参数：a是需要排序的数组，n是需要排序的元素个数
************************************************************************/ 
void InsertSort(int a[], int n)  
{     
	int i,j,temp;      
	/* 从无序区头部开始，将其中的每个元素插入到有序区  */
	for (i=1; i<n; i++)    
	{              
		temp = a[i];   /* 使用变量temp临时保存待插入元素a[i]  */
		for (j=i-1; j>=0 && temp < a[j]; j--) /*  在有序区中查找应插入的位置 */     
		{             
			a[j+1] = a[j];  /*  后移一个位置  */
		}        
		a[j+1] = temp;   /* 插入 */
	}  
} 
