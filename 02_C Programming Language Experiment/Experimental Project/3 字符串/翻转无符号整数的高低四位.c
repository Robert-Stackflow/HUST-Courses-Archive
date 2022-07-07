#include <stdio.h>
#include <stdlib.h>
/*编写完整的程序，从终端输入一个无符号短整数k，输出将k的高4位和低4位交换后的结果。*/
int main()
{
    int k;
    int i,j,l,m;
    scanf("%d",&k); 
    i=k/16/16/16%16;
    m=k/16/16%16;
    l=k/16%16;
    j=k%0x10;
    k=j*0x10*0x10*0x10+m*0x10*0x10+l*0x10+i;
    printf("%d",k);

}
