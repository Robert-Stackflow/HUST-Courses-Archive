#include<stdio.h>
int main(void)
{
	int h[10],max,ans=0;
	for(int i=0;i<10;i++) scanf("%d",&h[i]);
	scanf("%d",&max);
	max+=30;
	for(int i=0;i<10;i++)
		if(h[i]<=max) ans++;
 	printf("%d",ans);
}
