#include<stdio.h>
#include<stdlib.h>
int main(void)
{
	int number;
	printf("������һ�����֣�");
	scanf("%d",&number);
	int *a=(int *)malloc(number*sizeof(int));
	//���䶯̬�洢�ռ�
//	printf("%d\n",sizeof(a));
//	printf("%d\n",sizeof(*a));
	for(int i=0;i<number;i++)
		scanf("%d",(a+i));
	for(int i=0;i<number;i++)
		printf("%d ",*(a+i));
	free(a);//�ͷŶ�̬�洢�ռ�
	//�ͷŴ洢�ռ���޷��ٴ���ȷ���ָ��ָ�������
	for(int i=0;i<number;i++)
		printf("\n!!%d!!",*(a+i));
//	free(a);//�������ظ��ͷŶ�̬�洢�ռ�
}
