#include "stdio.h"
#define N 30
void main(void)
{
	  int score[N],i,sum=0;/* 声明成绩数组，循环控制变量，累加和变量并清零*/
	  double average; /* 声明平均分数变量 */
	  printf("input the scores please:\n"); /* 输出提示信息 */
	  for(i=0;i<N;i++)
		  scanf("%d",&score[i]);     /* 将键盘输入的成绩赋给各个数组元素 */
	  for(i=0;i<N;i++)
		  sum+=score[i];               /* 求学生成绩的累加和 */
	  average=1.0*sum/N;                /* 计算平均成绩 */
	  printf("sum=%d\n",sum);
	  printf("average=%lf\n",average);
}
