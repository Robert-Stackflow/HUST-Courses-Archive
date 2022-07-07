#include<stdio.h>
#include<stdbool.h>
int main(void)
{
    int n,i,x;
    bool flag=true;      /*flag：控制标记*/
    for(n=6;flag;n++)    /*采用试探的方法，令试探值n逐步加大*/
    {
        for(x=n,i=1;flag&&i<=5;i++)/*判断是否可以按照题目要求进行5次分配*/
        {
            if((x-1)%5==0) x=4*(x-1)/5;
            else flag=false;        /*若不能分配则设置标记flag=0，退出分配*/
        }
        if(flag) break;         /*若分配过程正常结束则找到结果退出试探过程*/
        else flag=true;        /*否则继续试探下一个数*/
    }
    printf("Total number of fish catched=%d\n",n);
    return 0;
}
