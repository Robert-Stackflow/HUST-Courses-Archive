#include "stdio.h"
#include "math.h"
struct point{ 	/* ƽ���ϵ�Ľṹ���� */
	int	x,y;		/* x,y�ǵ������ */
};
struct line{		/* ƽ�����߶ε�Ƕ�׽ṹ���� */
	char name[6];	/* �߶����� */
	struct point start;	/* �߶ε���� */
	struct point end;	/* �߶ε��յ� */
};
int main(void)
{	struct line a={"abc",{1,1},{10,10}}; /* ����Ƕ�׽ṹ����ʱ�����ʼ�� */
	double dx2,dy2,length;
	printf("line name is %s\n",a.name); /* ����߶����� */
	printf("starting point:(%d,%d)\n",a.start.x,a.start.y);/*����������*/
	printf("end point:(%d,%d)\n",a.end.x,a.end.y);/*����յ����� */
	scanf("%s",a.name);	/*�����߶���*/
	scanf("%d%d",&a.start.x,&a.start.y);/*�����������*/
	a.end.x=100;a.end.y=100;/*���յ����긳ֵ */
	dx2=(a.end.x-a.start.x)*(a.end.x-a.start.x);
	dy2=(a.end.y-a.start.y)*(a.end.y-a.start.y);
	length=sqrt(dx2+dy2);/*�����߶γ���*/
	printf("the tength is %lf\n",length);/*����߶γ���*/
  return 0;
}
