#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <timeb.h> 

#define N 1000000   /* 需要排序的数组元素的数量 */

void CreateData(int a[ ],int n,int low,int high) ; /* 生成随机数的函数原形 */
void InsertSort(int a[], int n) ;  /* 直接插入排序的函数原形 */
void ShellSort(int a[], int n) ;  
void MergeSort(int a[],int n);
void merge(int a[], int b[], int low, int mid, int high);
void MergePass(int a[], int b[], int len, int n);
int a[N];
int main()
{
	int i;
	long t;
	struct timeb  st1,st2;
	printf(" N=%d\n",N);
	CreateData(a,N,0,20000);  /* 生成随机数*/
    ftime(&st1);
	InsertSort(a, N);   /* 调用直接插入排序函数 */
    ftime(&st2);
  	t=st2.time*1000+st2.millitm- (st1.time*1000+st1.millitm);
	printf(" 插入 t=%ldms\n",t);

	CreateData(a,N,0,20000);  /* 生成随机数*/
    ftime(&st1);
	ShellSort(a, N);   /* 调用Shell排序函数 */
    ftime(&st2);
	t=st2.time*1000+st2.millitm- (st1.time*1000+st1.millitm);
	printf(" 希尔 t=%ldms\n",t);

	CreateData(a,N,0,20000);  /* 生成随机数*/
    ftime(&st1);
	MergeSort(a, N);   /* 调用归并排序函数 */
    ftime(&st2);
	t=st2.time*1000+st2.millitm- (st1.time*1000+st1.millitm);
	printf(" 归并 t=%ldms\n",t);
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