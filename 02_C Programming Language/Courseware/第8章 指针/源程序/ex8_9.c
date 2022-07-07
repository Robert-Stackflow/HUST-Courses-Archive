#include "stdio.h"
int main(void)
{	int a[5]={0,1,2,3,4};
	int *px=&a[0];/*px指向a[0]*/
	printf("display the address and the value of the elements:\n");
	for(;px<&a[0]+5;px++)/*若px<&a[5]，循环*/
		printf("px=%p  *px=%d\n",px,*px);/*输出各元素的地址、值*/
	px=&a[0];/*px指向a[0]*/
	printf("after executing px=&a[0]:\n");/*输出提示*/
	printf("px=%p  *px=%d\n",px,*px);/*输出a[0]的地址及值*/
	px+=3;/*px指向a[3]*/
	printf("after px plus 3:\n");/*输出提示*/
	printf("px=%p   *px=%d\n",px,*px);/*输出a[3]的地址及值*/
	px-=2;/*px指向a[1]*/
	printf("after px minus 2:\n");
	printf("px=%p  *px=%d\n",px,*px);/* px指向a[1]，*px=1*/
	printf("*(++px)=%d\n",*(++px));/*px先自增指向a[2]，再间访a[2]*/
	printf("*(px++)=%d\n",*(px++));/* *(px++)=2 */
	printf("px=%p  *px=%d\n",px,*px);/*输出px的值，即a[3]的地址，*px=3*/
	printf("*(--px)=%d\n",*(--px));/*px先自减指向a[2]，再间访a[2]*/
	printf("*(px--)=%d\n",*(px--));/**(px--)=2*/
	printf("px=%p  *px=%d\n",px,*px);/*px指向a[1]，输出a[1]的地址，*px=1*/
	return 0;
}
