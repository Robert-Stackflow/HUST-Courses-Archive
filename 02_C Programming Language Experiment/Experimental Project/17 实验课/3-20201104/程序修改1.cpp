#include<stdio.h>
#include<math.h>
int main(void)
{
	int i,x,k,flag=0;
	printf("�������жϺ���,���������1������,��ctrl+Z����\n");
	while(scanf("%d",&x)!=EOF)
	{
	for(i=2,k=x>>1;i<=k;i++)
	{
		if(x%i==0)
			{
				flag=1;
				k=i;
			}
	}	
	if(flag==1)
		printf("%d�Ǻ���\n",x);
	else
		printf("%d���Ǻ���\n",x);
	flag=0;
	}
	return 0;
 } 
