/*****************************************************
File name：Quicksort
Author：Zhengqijun    Version:1.0    Date: 2016/11/04
Description: 对数组进行快速排序
Funcion List: 实现快速排序算法
*****************************************************/

#include <stdio.h>
#include <stdlib.h>

#define BUF_SIZE 10

/**************************************************
 *函数名：display
 *作用：打印数组元素
 *参数：array - 打印的数组，maxlen - 数组元素个数
 *返回值：无
 **************************************************/
void display(int array[], int maxlen)
{
    int i;

    for(i = 0; i < maxlen; i++)
    {
        printf("%-3d ", array[i]);
    }
    printf("\n");

    return ;
}

/************************************
 *函数名：QuickSort
 *作用：快速排序算法
 *参数：
 *返回值：无
 ************************************/
void QuickSort(int *arr, int low, int high)
{
    if (low < high)
    {
        int i = low;
        int j = high;
        int k = arr[low];
        while (i < j)
        {
            while(i < j && arr[j] >= k)     // 从右向左找第一个小于k的数
            {
                j--;
            }

            if(i < j)
            {
                arr[i++] = arr[j];
            }

            while(i < j && arr[i] < k)      // 从左向右找第一个大于等于k的数
            {
                i++;
            }

            if(i < j)
            {
                arr[j--] = arr[i];
            }
        }

        arr[i] = k;
		            for(int i = 0; i <10; i++)
    {
        printf("%-3d ", arr[i]);
    }
    printf("\n");
        // 递归调用
        QuickSort(arr, low, i - 1);     // 排序k左边
        QuickSort(arr, i + 1, high);    // 排序k右边
    }
}

// 主函数
int main()
{
    int array[BUF_SIZE] = {503,87,512,61,908,170,897,275,653,426};
    int maxlen = BUF_SIZE;

    printf("排序前的数组\n");
    display(array, maxlen);

    QuickSort(array, 0, maxlen-1);  // 快速排序

    printf("排序后的数组\n");
    display(array, maxlen);

    return 0;
}
