#include<stdio.h> 
int main(void)
{
	int wage,tax,flag=1;
	while(flag)
	{
	printf("\n请输入工资：\n") ;//提示输入工资 
	scanf("%d",&wage);
	tax=(int)((wage)/1000);// 用于计算不同的工资范围 
	switch (tax)
	{
		case 0:	printf("您不用交税金！");break;
		case 1:	printf("您应交税金：%.3f",(float)wage*0.05);break;
		case 2:	printf("您应交税金：%.3f",(float)wage*0.1);break;
		case 3:	printf("您应交税金：%.3f",(float)wage*0.15);break;
		case 4:	printf("您应交税金：%.3f",(float)wage*0.2);break;
		default:printf("您应交税金：%.3f",(float)wage*0.25);break;
	}                     //强制类型转换，输出较为精确的浮点数 
	printf("\n是否需要继续计算？(0 or 1)\n\n");
	scanf("%d",&flag);//用于决定是否继续循环的语句 
	}
	return 0;
}
