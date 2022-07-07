#include "stdio.h"
#include "ctype.h"
#define NUMBER 100
int getint(int *pn); /* ��������ԭ��*/
int getint(int *pn) /*����getint����*/
{
	  int c,sign;
	  while(isspace(c=getchar()))       /* ����ǰ���ո� */ 
		;
	  if(!isdigit(c) && c!=EOF && c!= '+' && c!= '-') {
		/* ������Ϊ�����֡���EOF��Ҳ����+��-�ţ���ʾ�����ҷ��� */
		printf("input error!\n");
		return 0;
	  }
	  sign = (c=='-') ?-1:1;          /* ������� */
	  if(c=='+' || c=='-')
		  c=getchar();                  /* ����+��-�� */
	  for(*pn=0;isdigit(c);c=getchar())
		  *pn=10 * *pn+(c-'0');       /* �����ִ�ת��Ϊ��Ӧ���� */
	  *pn *= sign;                      /* ���������ķ��� */
	  return c; /* ���ص�cֵһ�����������ַ� */
}
int main(void)
{
	  int a[NUMBER],i,j,k;
	  printf("input integers ends with Enter\n");
	  for(i=0;i< NUMBER && (k=getint(&a[i]))!= '\n';) /*getint����ֵ����k,*/
		  if(k) i++; /* ����ֻҪ����ûԽ����kֵ���ǻ��з�������ѭ�� */
	  for(j=0;j<=i;j++)
		  printf("%8d",a[j]); /* ���ת������� */
	  printf("\n");
	  return 0;
}
