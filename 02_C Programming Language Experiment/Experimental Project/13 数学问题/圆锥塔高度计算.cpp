#include<stdio.h>
#include<math.h>
int main()
{
	int h=10;
	float x,y,d1,d2,d3,d4;
	scanf("%f%f",&x,&y);
	d1=sqrt((x-2)*(x-2)+(y-2)*(y-2));//��һ����Բ�� 
	d2=sqrt((x+2)*(x+2)+(y-2)*(y-2));//�ڶ�����Բ��
	d3=sqrt((x+2)*(x+2)+(y+2)*(y+2));//��������Բ��
	d4=sqrt((x-2)*(x-2)+(y+2)*(y+2));//��������Բ��
	if(d1>1&&d2>1&&d3>1&&d4>1) h=0;
	else if(d1<=1&&d2>1&&d3>1&&d4>1) h=10*(1-d1);
	else if(d1>1&&d2<=1&&d3>1&&d4>1) h=10*(1-d2);
	else if(d1>1&&d2>1&&d3<=1&&d4>1) h=10*(1-d3);
	else if(d1>1&&d2>1&&d3>1&&d4<=1) h=10*(1-d4);
	printf("�õ�ĸ߶�=%d\n",h);
	return 0;
}
