#include<stdio.h> 
int main(void)
{
	int wage,tax,flag=1;
	while(flag)
	{
	printf("\n�����빤�ʣ�\n") ;//��ʾ���빤�� 
	scanf("%d",&wage);
	tax=(int)((wage)/1000);// ���ڼ��㲻ͬ�Ĺ��ʷ�Χ 
	switch (tax)
	{
		case 0:	printf("�����ý�˰��");break;
		case 1:	printf("��Ӧ��˰��%.3f",(float)wage*0.05);break;
		case 2:	printf("��Ӧ��˰��%.3f",(float)wage*0.1);break;
		case 3:	printf("��Ӧ��˰��%.3f",(float)wage*0.15);break;
		case 4:	printf("��Ӧ��˰��%.3f",(float)wage*0.2);break;
		default:printf("��Ӧ��˰��%.3f",(float)wage*0.25);break;
	}                     //ǿ������ת���������Ϊ��ȷ�ĸ����� 
	printf("\n�Ƿ���Ҫ�������㣿(0 or 1)\n\n");
	scanf("%d",&flag);//���ھ����Ƿ����ѭ������� 
	}
	return 0;
}
