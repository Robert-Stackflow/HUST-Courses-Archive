#include<stdio.h>
void bubble_sort(int b[],int s)
{
	int i,j,t;
	for (i=0;i<s-1;i++)
	{
	for(j=0;j<s-i-1;j++)
		if(b[j]<b[j+1])
			t=b[j],b[j]=b[j+1],b[j+1]=t;
	printf("\n��%d������õ���",i+1); 
	for(int i=0;i<s;i++)
		printf("%d ",b[i]);
		printf("\n");	
}
}

int main(void)
{
	int x[10];
	int count;
	printf("����������������"); 
	scanf("%d",&count);
	for(int i=0;i<count;i++)
		scanf("%d",&x[i]);
	bubble_sort(x,count);
	return 0;
}
