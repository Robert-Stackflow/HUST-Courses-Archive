#include<stdio.h>
void bubble_sort(int b[],int cmd,int s); 
int BinarySearch(int nums[],int x,int n);
 // nums为目标数组,x为目标数字,n为数组个数长度
int main()
{
	int nums[100],count,found,cmd;
	printf("Input the count:");
	scanf("%d",&count);
	printf("Input the number you want to found:");
	scanf("%d",&found);
	printf("Input your numbers\n");
	for(int i=0;i<count;i++)	scanf("%d",&nums[i]);
	printf("Input your cmd for sort:(1 for increasing and 0 for declining):");
	scanf("%d",&cmd);
	bubble_sort(nums,cmd,count);
	int index=BinarySearch(nums,found,count);
	if(index!=-1)
		printf("find: a[%d]=%d!\n",index,nums[index]);
	else
		printf("NOT FOUND!\n");
	return 0;
}

void bubble_sort(int b[],int cmd,int s)
{
	int i,j,t;
	for (i=0;i<s-1;i++)
	{
	for(j=0;j<s-i-1;j++)
		if(cmd==1?b[j]<b[j+1]:b[j]>b[j+1])
			t=b[j],b[j]=b[j+1],b[j+1]=t;
	printf("\n第%d次排序得到：",i+1); 
	for(int i=0;i<s;i++)
		printf("%d ",b[i]);
		printf("\n");	
}
}
int BinarySearch(int nums[],int x,int n)
{
	int front=0,middle=0,back=n-1;
	while(front<=back){
	middle=(front+back)/2;
	if(nums[middle]>x) back=middle-1;
	else if(nums[middle]<x)	front=middle+1;
	else if(nums[middle]==x) return middle;
	}
	return -1;
}
