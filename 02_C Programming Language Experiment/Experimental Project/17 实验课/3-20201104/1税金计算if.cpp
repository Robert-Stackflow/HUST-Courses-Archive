#include<stdio.h> 
int main(void)
{
	int x,y,flag=1;
	while(flag){
	printf("\n�����빤�ʣ�\n") ;//��ʾ���빤��
	scanf("%d",&x);
		if(x<0)	printf("��������������"); 
		if(x<1000) printf("�����ý�˰��");
		if(x<2000&&x>=1000)printf("��Ӧ��˰��%.3f",(float)x*0.05);
		if(x<3000&&x>=2000)printf("��Ӧ��˰��%.3f",(float)x*0.1);
		if(x<4000&&x>=3000)printf("��Ӧ��˰��%.3f",(float)x*0.15);
		if(x<5000&&x>=4000)printf("��Ӧ��˰��%.3f",(float)x*0.2);
		if(x>5000)printf("��Ӧ��˰��%.3f",(float)x*0.25);
		//ǿ������ת���������Ϊ��ȷ�ĸ�����
	printf("\n�Ƿ���Ҫ�������㣿(0 or 1)\n\n");
	scanf("%d",&flag);//���ھ����Ƿ����ѭ�������
	}
	return 0;
}
