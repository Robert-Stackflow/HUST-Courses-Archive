#include <stdio.h>
#include <stdlib.h>
/*��д�����ĳ��򣬴��ն�����һ���޷��Ŷ�����k�������k�ĸ�4λ�͵�4λ������Ľ����*/
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
