/*  shell法对整型数组进行排序   */
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define N 10   /* 需要排序的数组元素的数量 */

void CreateData(int a[ ],int n,int low,int high) ; /* 生成随机数的函数原形 */
void ShellSort(int a[], int n) ;  /* 直接插入排序的函数原形 */

int main()
{
	int i,data[N];
	CreateData(data,N,0,100); /* 生成随机数*/
	printf("排序前：");
	for(i=0;i<N;i++)         /* 输出生成的随机数 */
		printf("%d  ",data[i]);
	ShellSort(data, N);   /* 调用直接插入排序函数 */
	printf("\n排序后：");
	for(i=0;i<N;i++)      /* 输出排序后的结果 */
		printf("%d  ",data[i]);
	printf("\n");
	return 0;
}
/***********************************************************************
　函数名称：CreateData
  函数功能：产生若干的随机整数。
　函数参数：a是保存生成数据的数组，
            n是元素个数，
			low是数据的最小值，
			high是数据的最大值
			函数返回值：无。
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
函数名称：ShellSort
函数功能：希尔排序算法,对n个整数递增排序。
          取序列的一半为初始间隔，以后每次减半，直到间隔为1。
函数参数：第1个参数a为数组名，保存待排序的整数；第2个参数n表示数组中元素个数
函数返回值：无。
************************************************************************/
void ShellSort(int a[],int n) 
{
	int gap,i,j,t;

	for(gap=n/2;gap>0;gap=gap/2) 	/* 初始间隔为n/2，以后每趟间隔缩小一半 */
	     for(i=gap;i<n;i++) /*  分别对各小组进行插入排序 */
		 {
			 t=a[i];
			 /*  对一组间隔为gap的元素进行插入排序   */
			 for(j=i-gap;j>=0&&a[j]>t;j-=gap) 
				 /* 把i之前大于a[i]的数据向后移动   */
				 a[j+gap]=a[j]; 
			 a[j+gap] = t; /* 在合适位置安放当前元素  */
		 }
}
	