#include<stdio.h> 
#include<time.h>
#include<stdlib.h>
#define	I 10
#define LIFE 3
int main(void)
{
	int x,y,i=1,count=0,life;
	srand((unsigned)(time(NULL)));
	printf("0����ʯͷ��1���������2����\n���������ִ��������������ƣ�\n"); 
	while(i<=I){
	scanf("%d",&x);
	y=rand()%3;
	if(x!=0&&x!=1&&x!=2)
		printf("���ݴ������ٴ����룡\n\n");
	else{
	if((x==0&&y==1)||(x==2&&y==0)||(x==1&&y==2))
		printf("��Ӯ�ˣ�\n\n");
	else if(x==y)
	 	printf("ƽ�֣�\n\n");
	else
		printf("�����ˣ�\n\n");
		++count;
	}
	++i;
	life=LIFE-count;
	if(i>1)
		printf("����һ�ְɣ�\n����ʣ%d����!\n",life); 
}
	return 0; 
}
