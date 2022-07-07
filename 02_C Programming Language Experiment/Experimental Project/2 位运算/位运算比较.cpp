#include<stdio.h>
int main(void)
{
	int num,s,m=0,count=0;
	int a[5000];
	scanf("%d",&s);
	int i=0;
	int j;
	j=s;
	while(m<=s)
	{
	scanf("%d",&a[m]);
	++m;
	}
	while((a[i]&a[j])>(a[i]^a[j]))
       {
		--j;
		++count;
		if (i==j)
		{
			++i;
		}
	}
	printf("%d",count);
	return 0;
}
