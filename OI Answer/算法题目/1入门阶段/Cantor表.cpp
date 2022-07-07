#include<stdio.h>
int n,i=1,j;
int main(void)
{
    scanf("%d",&n);
	for(;n>j;i++)	j+=i;
	i--;
    if(i%2)	printf("%d/%d",j-n+1,i+n-j);
    else	printf("%d/%d",i+n-j,j-n+1);
}
