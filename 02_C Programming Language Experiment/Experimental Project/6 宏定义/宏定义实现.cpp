#include<stdio.h>
#define  setbits(x,p,n,y)  (x&~(~(~0<< n)<<(p+1-n))|(y&~(~0<<n))<<(p+1-n))
//定义宏setbits(x,p,n,y)，取出整数y的最右边n位，
//将其作为整数x从第p位开始的向右n位（p从右至左编号为0~15），x的其余位保持不变。
int main(void)
{
	int x, y;
    int p, n;
    scanf("%d%d%d%d", &x,&p,&n,&y);
    printf("%d", setbits(x,p,n,y));
    return 0;
} 
