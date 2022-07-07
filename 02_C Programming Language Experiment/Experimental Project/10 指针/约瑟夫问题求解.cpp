# include<stdio.h>
int main (void)
{
	int M,N;
	int a[M],b[M];
	scanf("%d",&M);
	for (int i=0;i<M;i++)
        a[i]=i+1;
	int i,j,k;
	scanf("%d",&N);
    for(i=M,j=0;i>1;i--)
    {
    for(int k=1;k<=N;k++)
    {
    	if(a[k]==0) j++;
		if(++j>M-1)	j=0;
	}
    printf("j:%d\n",j);
    b[M-i]=(j?a[j-1]:a[i-1]);
    printf("%d\n",b[M-i]);
    a[b[M-i]-1]=0;
    printf("\n");
	}
    for (int i=0;i<M;i++)
    {
        if (a[i]!=0)
            printf("!!!%d!!!",a[i]);
    }
    return 0;
}

