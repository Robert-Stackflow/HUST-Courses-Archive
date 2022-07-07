#include<stdio.h>
int main(void)
{
	int n;
	scanf("%d",&n);
	while(n!=0)
    {
        if(n%2==0)printf("Alice\n");
        else printf("Bob\n");
        scanf("%d",&n);
    }
}
