#include<stdio.h> 
double abs(double a)//�������ֵ���� 
{
	if(a<0)
		a=-a;
	return a;
}
int main(void)
{
	double a,b,max=0;
	int day,flag=1;
	while(flag){
	printf("����������:\n");
	scanf("%d",&day);
	printf("��������Щ������̼۸�:\n");
	scanf("%lf",&b);//��ʾ��������������ÿ�����̼۸� 
	for(int i=1;i<day;++i)
		{
			a=b;
			scanf("%lf",&b);
			if(abs(a-b)>max)//if��佫ÿ�ε���󲨶�ֵ����max	
				max=abs(a-b);
		} 
	printf("\n��%d����󲨶�ֵΪ%.2lf\n",day,max);//�����󲨶�ֵ 
	max=0;
	printf("\n�Ƿ���Ҫ�������㣿(0 or 1)\n\n");
	scanf("%d",&flag);//���ھ����Ƿ����ѭ�������
	}
	
	return 0;
}
