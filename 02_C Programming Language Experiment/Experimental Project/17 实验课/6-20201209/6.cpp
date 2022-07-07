#include<stdio.h>
#include<stdlib.h>
#define MAX 100
void swap(int *n1,int *n2)
{
	int t;
	t=*n1;
	*n1=*n2;
	*n2=t;
}
void sort(int *nums,int n,int cmd){
    int i,j;
    for (i=0;i<n;i++)
        for(j=i+1;j<n;j++)
            if(cmd?(nums[i]>nums[j]):(nums[i]<nums[j]))
                swap(&nums[i],&nums[j]);
}
int main(int argc, char*argv[])
{
    int nums[MAX];
    int i=0,cmd=0,n=0;
	if(argv[2][0]=='-') {
            cmd=((argv[2][1]=='d')?0:1);
        }
    for(i=0;i<atoi(argv[1]);i++)
    	nums[n++]=atoi(argv[i+3]);
    sort(nums,n,cmd);
    for(int i=0;i<n;i++) printf("%d ",nums[i]);
    return 0;
}
