#include<stdio.h> 
int main(void)
{
	int score,max;
	printf("������һ���ɼ�������-1����\n");
	max=0;
	scanf("%d",&score);
	while(score!=-1) 
		{
			if(score>max)
				max=score;
		scanf("%d",&score);
		}
	printf("����ʤ�ߵķ�����%d",max);
	return 0;
}
