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
	printf("1����õ�壬2����ɻ���3����ĵ�����ڶ���������������Ķ���\n");
	scanf("%d%d",&m,&n);
	rose(n,m);
}
