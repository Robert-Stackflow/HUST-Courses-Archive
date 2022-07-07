/*  用归并排序法对n个整型进行升序排序  */
#include<stdio.h>
#include<stdlib.h>

#define N sizeof(a) / sizeof(*a)   /* 数组的长度 */

void MergeSort(int a[],int n);
void merge(int a[], int b[], int low, int mid, int high);
void MergePass(int a[], int b[], int len, int n);

int main(void)
{
	int i,a[] = {3, 5, 13, 6, 14, 17, 15, 7, 4};
    MergeSort(a, N);
    for(i = 0; i < N; i++)
       printf("%d  ", a[i]);
	printf("\n");
	return 0;
}

/********************************************************************************************
函数名称：Merge
函数功能：归并操作，将数组a中的两个有序子序列a[low]~a[mid]和a[mid+1]~a[high]归并为一个有序序列,
          结果放到b[low]~b[high]中.        
函数参数：
        a--存放待归并的两个有序序列的数组
		b--存放归并后有序序列的数组
		low-子序列1的起始位置
        mid--子序列1的末尾位置
		high--子序列2的末尾位置,其起始位置为mid+1
函数返回值：无。
*********************************************************************************************/
void merge(int a[], int b[], int low, int mid, int high)
{
    int k = low;     /* 结果序列的起始位置 */
    int i = low;     /* 子序列1的起始位置 */
    int j = mid + 1; /* 子序列2的起始位置 */

    /* 从两个子序列的起始位置，依次比较对应的元素，选择相对小的元素放入到合并空间，并移动到下一位置 ，直到某一序列达到尾。  */ 
	while(i <= mid && j <= high)
	{
        if(a[i] <= a[j])
            b[k++] = a[i++];
        else
            b[k++] = a[j++];
    }
	/* 另一序列剩下的所有元素直接复制到合并序列尾 */
    if(i <= mid)
        for(; i <= mid; i++)
            b[k++] = a[i];
    else
        for(; j <= high; j++)
            b[k++] = a[j];
}	

/***********************************************************************
函数名称：MergePass
函数功能：一趟归并排序的算法,对数组a中长为len的有序子序列（最后一个可能小于len），
          两两归并，结果放到b中。        
函数参数：
        a--需要排序的数组
		b--存放归并后有序序列的数组
		len-a中有序子序列的长度
        n--数组a的大小
函数返回值：无。
************************************************************************/ 
void MergePass(int a[], int b[], int len, int n)
{
    int start = 0,j;
    while(start <= n- 2 * len) /* n - 2 * len的意思是满足可两两归并的最低临界值 */
    {
        merge(a, b, start, start + len - 1, start + len * 2 - 1);
        start += 2 * len;
    }
    /* 如果一段是正好可归并的数量而另一段则少于正好可归并的数量 */
    if(start + len < n)
        merge(a, b, start, start + len - 1, n - 1);
    else
        for(j = start; j < n; j++) /* 如果只剩下一段或者更少的数量*/
            b[j] = a[j];
}

/***********************************************************************
函数名称：MergeSort
函数功能： 用归并排序法对n个整型进行升序排序。        
函数参数：
        a--需要排序的数组
        n--数组a的大小
函数返回值：无。
************************************************************************/ 
void MergeSort(int a[], int n)
{
    int *temp = (int *)malloc(sizeof(int)*n);
    int len = 1;
    while(len < n)
    {
        MergePass(a, temp, len, n);
        len += len;
        MergePass(temp, a, len, n);
        len += len;
    }
	free(temp);
}
