#include "stdio.h"
#define SIZE 3
double scalar(double *a,double *b,int n);
int main(void)
{
	  double x[SIZE],y[SIZE],*px,*py;
	  for(px=x;px<x+SIZE;px++)   /* x+SIZE��Ԫ��x[SIZE]�ĵ�ַ */
		  scanf("%lf",px);
	  getchar();/*��ȡ���з�*/
	  for(py=y;py<&y[SIZE];)     /* &y[SIZE]����y+SIZE����Ԫ��y[SIZE]�ĵ�ַ */
		  scanf("%lf",py++);
	  px=x;py=y;/*������ָ����Ϊʵ�ε���scalar����*/
	  printf("the scalar of vector x and vector y is %lf\n",scalar(px,py,SIZE));
	  return 0;
}
double scalar(double *a,double *b,int n) /*��ָ����Ϊ�βζ���scalar����*/
{ double s,*p;
	  printf("the vector a is\n");
	  for(p=a;p<a+n;)
		  printf("%lf\t",*p++);
	  printf("\nthe vector b is\n");
	  for(p=b;p<b+n;)              /* b+n��Ԫ��b[n]�ĵ�ַ */
		  printf("%lf\t",*p++);
	  printf("\n");
	  for(s=0,p=a;p<a+n;)          /* a+n��Ԫ��a[n]�ĵ�ַ */
		  s+=((*p++)*(*b++));
	  return s;
}
