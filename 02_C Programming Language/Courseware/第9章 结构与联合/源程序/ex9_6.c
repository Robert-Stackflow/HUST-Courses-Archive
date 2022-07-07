#include "stdio.h"
#include "math.h"
struct point{ 	/* 平面上点的结构类型 */
	int	x,y;		/* x,y是点的坐标 */
};
struct line{		/* 平面上线段的嵌套结构类型 */
	char name[6];	/* 线段名称 */
	struct point start;	/* 线段的起点 */
	struct point end;	/* 线段的终点 */
};
int main(void)
{	struct line a={"abc",{1,1},{10,10}}; /* 声明嵌套结构变量时对其初始化 */
	double dx2,dy2,length;
	printf("line name is %s\n",a.name); /* 输出线段名称 */
	printf("starting point:(%d,%d)\n",a.start.x,a.start.y);/*输出起点坐标*/
	printf("end point:(%d,%d)\n",a.end.x,a.end.y);/*输出终点坐标 */
	scanf("%s",a.name);	/*输入线段名*/
	scanf("%d%d",&a.start.x,&a.start.y);/*输入起点坐标*/
	a.end.x=100;a.end.y=100;/*对终点坐标赋值 */
	dx2=(a.end.x-a.start.x)*(a.end.x-a.start.x);
	dy2=(a.end.y-a.start.y)*(a.end.y-a.start.y);
	length=sqrt(dx2+dy2);/*计算线段长度*/
	printf("the tength is %lf\n",length);/*输出线段长度*/
  return 0;
}
