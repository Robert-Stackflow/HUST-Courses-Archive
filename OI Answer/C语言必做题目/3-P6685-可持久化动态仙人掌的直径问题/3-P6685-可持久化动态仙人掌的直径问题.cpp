#include<stdio.h>
#include<math.h>
int main(void)
{
	int n,m,x,count=0;
	scanf("%d%d",&n,&m);
	for(x=1;x<=n;x++)
	{
	float number=pow(x,m);
	if(number<=n) ++count;
	else break;
	}
	printf("%d",count);
}
