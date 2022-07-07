#include<stdio.h> 
#include<time.h>
#include<stdlib.h>

#define count 3 
int main(void)
{

	int i=0,x;
    char b;
    int flag;
    int age,plus,minus;
	do
	{
		srand((unsigned)(time(NULL)));
		age=rand()%100;
		plus=rand()%8;
		minus=rand()%8; 
		while(i<count)
    {
    i++;
        printf("\n请输入你猜的年龄:");
        scanf("%d",&x);
        if(x>age)
            printf("你真不会说话\n");
        else if(x>=0&&x<age)
          printf("你可真会说话，我太开心了\n");  
        else
        {	printf("恭喜你，猜对了\n");
			printf("\n是否继续下一轮游戏?\n继续游戏请输入1，退出游戏输入0\n") ;
			scanf("%d",&flag);
			i=0;
		}  
        if(i==count-1)
		{
			int need;
			printf("\n是否需要提示?\n需要请输入1，不需要输入0\n") ;	
			scanf("%d",&need);
			if(need)
			{
				int lower;
				lower=age-minus;
				if(lower<=0)
					lower=1;
				printf("实际年龄在[%d,%d]之间，你一定可以猜对！",lower,age+plus);
			}
				
		} 
		if(i==count&&x!=age){
		printf("\n很遗憾，您的次数用完了！\n");
		printf("实际年龄是%d!\n",age); 
		printf("\n是否继续下一轮游戏?\n继续游戏请输入1，退出游戏输入0\n") ;
		scanf("%d",&flag);
		i=0;
		}
	}
}while(flag==1);
return 0; 
}
