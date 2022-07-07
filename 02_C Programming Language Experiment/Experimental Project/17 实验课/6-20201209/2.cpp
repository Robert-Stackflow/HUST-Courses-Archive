#include<stdio.h>  
int RemoveSame(int *nums,int number); 
int main(void)
{
	int nums[100],number,len=2;
	scanf("%d",&number);
	for(int i=0;i<number;i++)
		scanf("%d",nums+i);
	len=RemoveSame(nums,number);
	for(int i=0;i<len;i++)
	{
		printf("%d",*(nums+i));
		if(i<len-1)	printf(" ");
	}
	printf("\n%d",len);
}

int RemoveSame(int *nums,int number)
{
	int check=*nums,j=1;
	for(int i=0;i<number;i++)
	{
		if(*(nums+i)!=check)
		{
			*(nums+j)=*(nums+i);
			check=*(nums+i);
			++j;
		}
	}
	return j;
}
