#include "stdio.h"
int main(void)
{	int a[5]={0,1,2,3,4};
	int *px=&a[0];/*pxָ��a[0]*/
	printf("display the address and the value of the elements:\n");
	for(;px<&a[0]+5;px++)/*��px<&a[5]��ѭ��*/
		printf("px=%p  *px=%d\n",px,*px);/*�����Ԫ�صĵ�ַ��ֵ*/
	px=&a[0];/*pxָ��a[0]*/
	printf("after executing px=&a[0]:\n");/*�����ʾ*/
	printf("px=%p  *px=%d\n",px,*px);/*���a[0]�ĵ�ַ��ֵ*/
	px+=3;/*pxָ��a[3]*/
	printf("after px plus 3:\n");/*�����ʾ*/
	printf("px=%p   *px=%d\n",px,*px);/*���a[3]�ĵ�ַ��ֵ*/
	px-=2;/*pxָ��a[1]*/
	printf("after px minus 2:\n");
	printf("px=%p  *px=%d\n",px,*px);/* pxָ��a[1]��*px=1*/
	printf("*(++px)=%d\n",*(++px));/*px������ָ��a[2]���ټ��a[2]*/
	printf("*(px++)=%d\n",*(px++));/* *(px++)=2 */
	printf("px=%p  *px=%d\n",px,*px);/*���px��ֵ����a[3]�ĵ�ַ��*px=3*/
	printf("*(--px)=%d\n",*(--px));/*px���Լ�ָ��a[2]���ټ��a[2]*/
	printf("*(px--)=%d\n",*(px--));/**(px--)=2*/
	printf("px=%p  *px=%d\n",px,*px);/*pxָ��a[1]�����a[1]�ĵ�ַ��*px=1*/
	return 0;
}
