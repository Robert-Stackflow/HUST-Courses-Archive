#include "stdio.h"
#define SIZE 3
double scalar(double *a,double *b,int n);
int main(void)
{
	  double x[SIZE],y[SIZE],*px,*py;
	  for(px=x;px<x+SIZE;px++)   /* x+SIZE是元素x[SIZE]的地址 */
		  scanf("%lf",px);
	  getchar();/*读取换行符*/
	  for(py=y;py<&y[SIZE];)     /* &y[SIZE]就是y+SIZE，是元素y[SIZE]的地址 */
		  scanf("%lf",py++);
	  px=x;py=y;/*下面用指针作为实参调用scalar函数*/
	  printf("the scalar of vector x and vector y is %lf\n",scalar(px,py,SIZE));
	  return 0;
}
double scalar(double *a,double *b,int n) /*以指针作为形参定义scalar函数*/
{ double s,*p;
	  printf("the vector a is\n");
	  for(p=a;p<a+n;)
		  printf("%lf\t",*p++);
	  printf("\nthe vector b is\n");
	  for(p=b;p<b+n;)              /* b+n是元素b[n]的地址 */
		  printf("%lf\t",*p++);
	  printf("\n");
	  for(s=0,p=a;p<a+n;)          /* a+n是元素a[n]的地址 */
		  s+=((*p++)*(*b++));
	  return s;
}
