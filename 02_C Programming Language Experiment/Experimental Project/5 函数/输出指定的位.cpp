#include<stdio.h>
//请根据step3_main.cpp中的主函数流程，补全此函数
int digit(long n, int k)
{
	/**********  Begin  **********/
    int array[10000],i=0;
    do{
        array[i]=n%10;
        n/=10;
        i++;
    }    
    while(n>0);
    if(k>i)
    return -1;
    else
    return array[k-1];
    /**********  End  **********/
}
int main(void)
{
	long n;
    int k;
    scanf("%ld%d",&n,&k);
    if( n < 0)
        n = -n;
    printf("%d",digit(n,k));
    return 0;
} 
