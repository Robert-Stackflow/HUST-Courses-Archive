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
        printf("\n��������µ�����:");
        scanf("%d",&x);
        if(x>age)
            printf("���治��˵��\n");
        else if(x>=0&&x<age)
          printf("������˵������̫������\n");  
        else
        {	printf("��ϲ�㣬�¶���\n");
			printf("\n�Ƿ������һ����Ϸ?\n������Ϸ������1���˳���Ϸ����0\n") ;
			scanf("%d",&flag);
			i=0;
		}  
        if(i==count-1)
		{
			int need;
			printf("\n�Ƿ���Ҫ��ʾ?\n��Ҫ������1������Ҫ����0\n") ;	
			scanf("%d",&need);
			if(need)
			{
				int lower;
				lower=age-minus;
				if(lower<=0)
					lower=1;
				printf("ʵ��������[%d,%d]֮�䣬��һ�����Բ¶ԣ�",lower,age+plus);
			}
				
		} 
		if(i==count&&x!=age){
		printf("\n���ź������Ĵ��������ˣ�\n");
		printf("ʵ��������%d!\n",age); 
		printf("\n�Ƿ������һ����Ϸ?\n������Ϸ������1���˳���Ϸ����0\n") ;
		scanf("%d",&flag);
		i=0;
		}
	}
}while(flag==1);
return 0; 
}
