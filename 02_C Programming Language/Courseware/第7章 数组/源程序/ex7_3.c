#include "stdio.h"
#define N 30
void main(void)
{
	  int score[N],i,sum=0;/* �����ɼ����飬ѭ�����Ʊ������ۼӺͱ���������*/
	  double average; /* ����ƽ���������� */
	  printf("input the scores please:\n"); /* �����ʾ��Ϣ */
	  for(i=0;i<N;i++)
		  scanf("%d",&score[i]);     /* ����������ĳɼ�������������Ԫ�� */
	  for(i=0;i<N;i++)
		  sum+=score[i];               /* ��ѧ���ɼ����ۼӺ� */
	  average=1.0*sum/N;                /* ����ƽ���ɼ� */
	  printf("sum=%d\n",sum);
	  printf("average=%lf\n",average);
}
