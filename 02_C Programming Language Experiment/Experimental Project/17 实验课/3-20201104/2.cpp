#include<stdio.h> 
int main(void)
{
	for(int i=100;i<=999;i++) //forѭ�����ȷ������λ�� 
	{
		int t;
		t=i*i;
		if(t%1000==i)//if�жϸ���ƽ��ĩ��λ�Ƿ��Ǹ������� 
			printf("%d\n",i);//�����Ϊ�棬�����ֵ�� 
	}
	return 0;
}
