#include <stdio.h>
#include <malloc.h>
#include <time.h>

void joseph(int count, int doom);

void joseph(int count, int doom) {
	int alive = count;	// �Ҵ�����
	int curIndex = 0;			// ��ǰ���±�
	int preIndex = count - 1; // ǰһ�����±�
	int *circle = NULL;
	int index;
	
	circle = (int *) malloc(sizeof(int) * count);
	for(index = 0; index < count; index++) {
		circle[index] = (index + 1) % count;	// ��ʼ������
	}
	
	while(alive > 0) {	// ֻҪ�����Ҵ��ߣ��ͼ�����ɱ��
		int num = doom % alive - 1; // ֱ�Ӽ������Ҫ�ƶ���������
		// ֱ�Ӷ�λ��Ҫ��Ȧ����
		for(index = 0; index < (num == -1 ? alive - 1 : num); index++) {
			preIndex = curIndex;
			curIndex = circle[curIndex];
		}
		// ���˳�Ȧ��
		printf("%d\n", curIndex+1);
		alive--;
		circle[preIndex] = circle[curIndex]; // �����ĳ�Ȧ������
		curIndex = circle[curIndex]; // ����������һ����
	}
	// ����㷨��normalJoseph.cЧ�����30%��
	
	free(circle);
}

int main() {
	int count;	// ������
	int doom;		// ������
	long startTime;
	long endTime;
	long deltaTime;
	
	printf("��������������������:");
	scanf("%d%d", &count, &doom);
	
	startTime = clock(); 
	// clock()������ȡ�ôӳ���ʼ���е�ִ�иú���ʱ�������ĺ�������
	joseph(count, doom);
	endTime = clock();
	
	deltaTime = endTime - startTime;
	printf("%ld.%03ld\n", deltaTime/1000, deltaTime%1000);
	
	return 0;
}
