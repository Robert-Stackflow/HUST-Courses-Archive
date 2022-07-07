#include <stdio.h>
#include <malloc.h>
#include <time.h>

void joseph(int count, int doom);

void joseph(int count, int doom) {
int alive = count;				// �Ҵ�����
	int number = 0;				// ��������
	int curIndex = 0;			// ��ǰ���±�
	int preIndex = count - 1;   // ǰһ�����±�
	int *circle = NULL;
	int index;

	circle = (int *) malloc (sizeof(int) * count);
	//��circle������г�ʼ�� 
	for(index = 0; index < count; index++) {
		circle[index] = (index + 1) % count;
	}

	while(alive > 0) {
		number++;
		if(number == doom) {
			alive == 1 ? printf("%d", curIndex+1) : printf("%d,", curIndex+1); 
			alive--;
			number = 0;
			circle[preIndex] = circle[curIndex];	//��Ȧ���� 
		} else {
			preIndex = curIndex;	//������һ���� 
		}
		curIndex = circle[curIndex];
	}

	free(circle);
}

int main(){
	int count;	// ������
	int doom;		// ������
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
	
}
