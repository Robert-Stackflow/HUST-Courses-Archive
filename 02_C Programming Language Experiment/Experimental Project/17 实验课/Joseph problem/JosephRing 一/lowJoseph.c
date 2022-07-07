#include <stdio.h>
#include <malloc.h>
#include <time.h>

void joseph(int count, int doom);

void joseph(int count, int doom) {
	int alive = count;		//�Ҵ����� 
	int number = 0;			//��������number==doomʱ����̭����� 
	int index = 0;			//�±꣬Ϊ������-1 
	int *circle = NULL;		//����������Ϊѭ�����飬�洢ÿ���� 

	//��calloc()��������õ��Ŀռ䣬�Զ���ʼ��ÿ��Ԫ��Ϊ0
	//���ԣ�0��ʾ���������Լɪ���ڣ�1��ʾ����˳�Ȧ��������̭�� 
	circle = (int *) calloc(sizeof(int), count);

	//ֻҪ�Ҵ���������0����һֱ����ѭ�� 
	while(alive > 0) {
		number += 1- circle[index];	//ÿ�ֵ�һ���˱�����������"0"����"1"�����м��� 
		if(number == doom) {		//��number==doomʱ����Ҫ��̭��ǰ�����
			/*
				��̭һ������Ҫ���Ĳ�������
					1���������˵�λ�� 
					2��������˵�״̬����Ȧ��"0"��Ϊ����Ȧ��"1" 
					3���Ҵ�����alive-- 
					4�� ������number���� 
			*/ 
			alive == 1 ? printf("%d", index+1) : printf("%d,", index+1);
			circle[index] = 1;
			alive--;
			number = 0;
		}
		//��������countȡ�࣬�����ʹindex��0~count-1֮�� һֱѭ�����ﵽѭ�������Ŀ�� 
		index = (index +1) % count;	
	}

	free(circle);		//������һ��Ҫ�ͷ�circle������Ŀռ� 
}

int main() {
	int count;  //������ 
	int doom;	//������	 
	long startTime;
	long endTime;
	long deltaTime;
	
	printf("��������������������:");
	scanf("%d%d", &count, &doom);
	
	startTime = clock();	 
	joseph(count, doom);
	endTime = clock();
	
	deltaTime = endTime - startTime;
	printf("\n%ld.%03ld\n", deltaTime/1000, deltaTime%1000);

	return 0;
}
