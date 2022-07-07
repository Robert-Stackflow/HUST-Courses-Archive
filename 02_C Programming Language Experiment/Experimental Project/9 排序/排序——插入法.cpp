#include <stdio.h>
int main(void)
{
    int a[1001];
    int i,j,t,count;
    int time=1;
    printf("请输入数字个数："); 
    scanf("%d",&count);
    for(i=0;i<count;++i)
        scanf("%d",a[i]);
    for(i=1;i<count;++i)
    {
        t=a[i];
        for(j=i-1;j>-1&&a[j]>t;j--)
            a[j+1]=a[j];
        a[j+1]=t;
        printf("\n第%d次得到的结果是:",time);
        for(int j=0;j<count;++j)
            printf("%d\t",a[j]);
        printf("\n");
        ++time;
    }
 
    return 0;
}
