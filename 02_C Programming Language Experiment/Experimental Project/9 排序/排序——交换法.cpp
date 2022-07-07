#include <stdio.h>
int main(void)
{
    int a[1000];
    int count,i,j,temp;
    scanf("%d",&count);
    for(i=0;i<count;++i)
        scanf("%d",&a[i]);
    for(i=0;i<count-1;++i)
    {
        for(j=i+1;j<count;++j)
        {
            if(a[i]>a[j])
            {
                temp=a[i];
                a[i]=a[j];
                a[j]=temp;
            }
        }
        printf("\n第%d次得到的结果是:",i+1);
        for(j=0;j<count;++j)
            printf("%d\t",a[j]);
        printf("\n");
    }
 
    return 0;
}
