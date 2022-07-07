#include<stdio.h> 
#include<time.h>
#include<stdlib.h>
#define	I 10
#define LIFE 3
int main(void)
{
	int x,y,i=1,count=0,life;
	srand((unsigned)(time(NULL)));
	printf("0代表石头，1代表剪刀，2代表布\n请输入数字代表你所出的手势：\n"); 
	while(i<=I){
	scanf("%d",&x);
	y=rand()%3;
	if(x!=0&&x!=1&&x!=2)
		printf("数据错误！请再次输入！\n\n");
	else{
	if((x==0&&y==1)||(x==2&&y==0)||(x==1&&y==2))
		printf("你赢了！\n\n");
	else if(x==y)
	 	printf("平手！\n\n");
	else
		printf("你输了！\n\n");
		++count;
	}
	++i;
	life=LIFE-count;
	if(i>1)
		printf("再来一局吧！\n您还剩%d条命!\n",life); 
}
	return 0; 
}
