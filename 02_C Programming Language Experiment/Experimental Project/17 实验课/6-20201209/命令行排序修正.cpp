#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
void sort(int cmd,int *nums);
int main(int argc, char*argv[])
{
    int *nums,k,flag=0;
    k=atoi(argv[1]);
    nums=(int *)malloc(k*sizeof(int));
    int i=0,cmd=0,j;
	for(i=0;i<k;i++)
    	scanf("%d",&nums[i]);
	if(argc>2) cmd=0;
	else cmd=1;
    int *p=&nums[0];
	sort(cmd,p);
    for(i=0;i<k;i++) printf("%d ",nums[i]);
    return 0;
}
void sort(int cmd,int *nums){
	int i,j,k;
	for (i=0;i<k;i++)
        for(j=i+1;j<k;j++)
            if(cmd?(*(nums+i)>*(nums+j)):(*(nums+i)<*(nums+j)))
            {
				int t;
				t=*(nums+i);
				*(nums+i)=*(nums+j);
				*(nums+j)=t;
			}
}
