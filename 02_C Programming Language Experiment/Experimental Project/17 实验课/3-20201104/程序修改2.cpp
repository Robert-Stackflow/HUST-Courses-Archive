#include<stdio.h>
#include<math.h>
int main(void)
{
	int i,x,k,flag=0;
	printf("�������жϺ���,���������1������,��ctrl+Z����\n");
	while(scanf("%d",&x)!=EOF)
	{
	int i=2;
	int k;
	k=x>>1;
	do{
		if(x%i==0)
			{
				flag=1;
				break;
			}
			i++;
	}while(i<=k);	
	if(flag==1)
		printf("%d�Ǻ���\n",x);
	else
		printf("%d���Ǻ���\n",x);
	flag=0;
	}
	return 0;
 } 
