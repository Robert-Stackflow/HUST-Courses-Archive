#include<stdio.h>
int rose(int m,int n)
{
	switch(n)
	{
		case 1:{for(int i=1;i<=n;i++)
					printf("meigui\n"); 
					break; }
		case 2:{for(int i=1;i<=n;i++)
					printf("hehua\n"); 
					break;}
		case 3:{for(int i=1;i<=n;i++)
					printf("mudan\n");	
					break;	}
	} 
} 
int main(void)
{
	int m,n;
	printf("1代表玫瑰，2代表荷花，3代表牡丹，第二次输入的数代表花的朵数\n");
	scanf("%d%d",&m,&n);
	rose(n,m);
}
