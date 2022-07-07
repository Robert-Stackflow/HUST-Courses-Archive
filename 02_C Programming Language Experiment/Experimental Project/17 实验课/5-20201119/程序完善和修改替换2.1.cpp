# include<stdio.h>
# include<string.h>
int main (void)
{
	int M,N;
	scanf("%d%d",&M,&N); 
	int a[M],b[M];
	int i,j,k;
	for(i=0;i<M;i++)
		a[i]=i+1;
	for(i=M,j=0;i>1;i--)     
	{
	for(k=1;k<=N;k++)
		if(++j>i-1)	j=0;
		b[M-i]=(j?a[j-1]:a[i-1]);
	if(j)
		for(k=--j;k<i;k++)
			a[k]=a[k+1];
	}
//	for(i=0;i<M-1;i++)
//		printf("%d\n",b[i]);	
	printf("%d",a[0]);
	return 0;
}

