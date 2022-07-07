#include<stdio.h> 
int main(void)
{
	int x,y,flag=1;
	while(flag){
	printf("\n请输入工资：\n") ;//提示输入工资
	scanf("%d",&x);
		if(x<0)	printf("请输入正整数！"); 
		if(x<1000) printf("您不用交税金！");
		if(x<2000&&x>=1000)printf("您应交税金：%.3f",(float)x*0.05);
		if(x<3000&&x>=2000)printf("您应交税金：%.3f",(float)x*0.1);
		if(x<4000&&x>=3000)printf("您应交税金：%.3f",(float)x*0.15);
		if(x<5000&&x>=4000)printf("您应交税金：%.3f",(float)x*0.2);
		if(x>5000)printf("您应交税金：%.3f",(float)x*0.25);
		//强制类型转换，输出较为精确的浮点数
	printf("\n是否需要继续计算？(0 or 1)\n\n");
	scanf("%d",&flag);//用于决定是否继续循环的语句
	}
	return 0;
}
