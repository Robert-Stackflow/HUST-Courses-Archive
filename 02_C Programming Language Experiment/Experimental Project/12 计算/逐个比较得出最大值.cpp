#include<stdio.h> 
int main(void)
{
	int score,max;
	printf("请输入一串成绩，并以-1结束\n");
	max=0;
	scanf("%d",&score);
	while(score!=-1) 
		{
			if(score>max)
				max=score;
		scanf("%d",&score);
		}
	printf("最终胜者的分数是%d",max);
	return 0;
}
