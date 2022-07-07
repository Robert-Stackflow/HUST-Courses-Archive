#include <stdio.h>
#include <malloc.h>
#include <time.h>

void joseph(int count, int doom);

void joseph(int count, int doom) {
int alive = count;				// 幸存人数
	int number = 0;				// 报数的数
	int curIndex = 0;			// 当前人下标
	int preIndex = count - 1;   // 前一个人下标
	int *circle = NULL;
	int index;

	circle = (int *) malloc (sizeof(int) * count);
	//对circle数组进行初始化 
	for(index = 0; index < count; index++) {
		circle[index] = (index + 1) % count;
	}

	while(alive > 0) {
		number++;
		if(number == doom) {
			alive == 1 ? printf("%d", curIndex+1) : printf("%d,", curIndex+1); 
			alive--;
			number = 0;
			circle[preIndex] = circle[curIndex];	//出圈操作 
		} else {
			preIndex = curIndex;	//处理下一个人 
		}
		curIndex = circle[curIndex];
	}

	free(circle);
}

int main(){
	int count;	// 总人数
	int doom;		// 厄运数
	long startTime;
	long endTime;
	long deltaTime;
	
	printf("请输入总人数、厄运数:");
	scanf("%d%d", &count, &doom);
	
	startTime = clock();
	joseph(count, doom);
	endTime = clock();
	
	deltaTime = endTime - startTime;
	printf("\n%ld.%03ld\n", deltaTime/1000, deltaTime%1000);
	
}
