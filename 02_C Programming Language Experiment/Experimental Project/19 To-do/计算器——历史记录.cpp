//存历史记录，数据类型扩展，while语句循环 
#include<stdio.h> 
int main(void)
{
	double x,y,z;
	int i=0,flag=1,history;
    char c,s[1000];
    printf("请按数字 运算符 数字的格式输入\n"); 
    while(flag)
    {
		scanf("%lf%s%lf",&x,&c,&y);
   		if (c=='+')
        z=(float)(x+y);
    	if (c=='-')
        z=(float)(x-y);
    	if (c=='*')
        z=(float)(x*y);
    	if (c=='/')  
        z=(float)(x/y); 
    	printf("%lf",z);
    	s[i]=(int)z;
    	printf("\n\n是否需要继续计算？\n如需要输入1，否则输入0\n\n");
    	scanf("%d",&flag);
    	i++;
	}
	if(flag==0)
	{
		printf("\n\n是否需要导出历史记录？\n如需要输入1，否则输入0\n\n");
		scanf("%d",&history);
		if(history)
			printf("%s",s);
	}
    return 0;
}
