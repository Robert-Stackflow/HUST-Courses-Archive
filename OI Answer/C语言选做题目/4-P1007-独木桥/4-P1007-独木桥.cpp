#include<stdio.h>
#define max(x,y) (((x)>(y))?(x):(y))
#define min(x,y) (((x)<(y))?(x):(y))
int main(void)
{
	int len,n,place,ans_max=0,ans_min=0;
	scanf("%d%d",&len,&n);
//	int pos[5001]={0};
	for(int i=1;i<=n;i++)
    {
        scanf("%d",&place);
        ans_max=max(ans_max,max(place,len+1-place));
        ans_min=max(ans_min,min(place,len+1-place));
    }
    printf("%d %d",ans_min,ans_max);
}
