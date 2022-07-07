
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
void CountSort(int a[], int n,int k);

#define N 10
int a[N];

int main()
{

	int k=150,i;
	long t;
	srand(time(NULL));
	for (i = 0; i < N; i++) 
	{
		a[i] = rand()%(k+1);
	}
	printf("排序前\n");
	for (i = 0; i < N; i++) 
	{
		printf("%4d",a[i]);
	}
	printf("\n排序后\n");
    CountSort(a,N,k);
	for (i = 0; i < N; i++) 
	{
		printf("%4d",a[i]);
	}
	printf("\n");
    return 0;
}

/************************************************************************************
函数名称： CountSort
函数功能：适合于小范围集合的计数排序,算法复杂度 O(n) 。
  已知数量范围为0～k，创建一个长度为（k+1）的数组buf，其中每个元素值是排序数组中对应记录的出现个数
  假设要排序的数组为a= {1,0,3,1,0,1,1}，这里最大值为3，最小值为0，那么
  创建一个数组长度为4的数组buf.
  然后一趟扫描数组a，得a中各个元素的总数，并保持到数组buf的对应单元中。
  比如0 的出现次数为2次，则 buf[0] = 2; 1 的出现次数为4次，则buf[1] = 4，。。。
  buf={2,4,0,1}.
  把这个在buf中的记录按每个元素的计数展开到输出回数组a中，排序就完成了。
  也就是 a[0] 到 a[1] 为0，  a[2] 到 a[5] 为1 这样依此类推。

函数参数：
        n ：数组a的大小。
        a ：待排序数据。
		k: 被排序元素的范围0~k
函数返回值：无。
************************************************************************************/
void CountSort(int a[], int n,int k)
{
	int *buf = (int *)malloc(sizeof(int)*(k+1));
	int i,j;
	
    for ( i = 0; i <=k ; ++i)//初始化记数为0
    {
        buf[i] = 0;
    }

	for (j = 0; j < n; j++)  // 对排序元素记数。在排序的值相应记数加1。
        buf[ a[j] ]++;
	for (j = i = 0; i <= k; i++) {//按每个元素的计数展开到输出回数组a中，排序就完成了
		while (buf[i]-- > 0) {
			a[j++] = i;
		}
	}
}
