#include<stdio.h>
#include<math.h>
int main()
{
	int h=10;
	float x,y,d1,d2,d3,d4;
	scanf("%f%f",&x,&y);
	d1=sqrt((x-2)*(x-2)+(y-2)*(y-2));//第一象限圆心 
	d2=sqrt((x+2)*(x+2)+(y-2)*(y-2));//第二象限圆心
	d3=sqrt((x+2)*(x+2)+(y+2)*(y+2));//第三象限圆心
	d4=sqrt((x-2)*(x-2)+(y+2)*(y+2));//第四象限圆心
	if(d1>1&&d2>1&&d3>1&&d4>1) h=0;
	else if(d1<=1&&d2>1&&d3>1&&d4>1) h=10*(1-d1);
	else if(d1>1&&d2<=1&&d3>1&&d4>1) h=10*(1-d2);
	else if(d1>1&&d2>1&&d3<=1&&d4>1) h=10*(1-d3);
	else if(d1>1&&d2>1&&d3>1&&d4<=1) h=10*(1-d4);
	printf("该点的高度=%d\n",h);
	return 0;
}
