#include<stdio.h>
#include<stdlib.h>
int main(void)
{
    long long num[102];
    int i;
    for(i=0;;i++)
    {
    scanf("%lld",&num[i]);
    if(num[i]==0) break;
	}
	i--;
	for(;i>=0;i--) printf("%lld ",num[i]);
	return 0;
}
