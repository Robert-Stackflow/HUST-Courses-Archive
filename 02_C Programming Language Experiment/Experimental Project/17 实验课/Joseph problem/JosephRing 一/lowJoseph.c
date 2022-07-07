#include <stdio.h>
#include <malloc.h>
#include <time.h>

void joseph(int count, int doom);

void joseph(int count, int doom) {
	int alive = count;		//幸存人数 
	int number = 0;			//计数，当number==doom时，淘汰这个人 
	int index = 0;			//下标，为总人数-1 
	int *circle = NULL;		//根据需求设为循环数组，存储每个人 

	//用calloc()函数申请得到的空间，自动初始化每个元素为0
	//所以，0表示在这个人在约瑟夫环内，1表示这个人出圈，即“淘汰” 
	circle = (int *) calloc(sizeof(int), count);

	//只要幸存人数大于0，则一直进行循环 
	while(alive > 0) {
		number += 1- circle[index];	//每轮到一个人报数，不管是"0"还是"1"都进行计数 
		if(number == doom) {		//当number==doom时，就要淘汰当前这个人
			/*
				淘汰一个人需要做四步操作：
					1、输出这个人的位置 
					2、把这个人的状态从在圈内"0"改为不在圈内"1" 
					3、幸存人数alive-- 
					4、 计数器number归零 
			*/ 
			alive == 1 ? printf("%d", index+1) : printf("%d,", index+1);
			circle[index] = 1;
			alive--;
			number = 0;
		}
		//与总人数count取余，则可以使index在0~count-1之间 一直循环，达到循环数组的目的 
		index = (index +1) % count;	
	}

	free(circle);		//结束后一定要释放circle所申请的空间 
}

int main() {
	int count;  //总人数 
	int doom;	//厄运数	 
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

	return 0;
}
