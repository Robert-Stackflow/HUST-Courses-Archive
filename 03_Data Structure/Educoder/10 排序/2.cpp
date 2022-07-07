#include "stdio.h"
#include "stdlib.h"
int MidValue(int a[],int n);
int main()
{
int ans,*a,n,i;
scanf("%d",&n);
a=(int *)malloc(sizeof(int)*n);
for(i=0;i<n;i++)
    scanf("%d",&a[i]);
printf("%d",MidValue(a,n));
free(a);
return 1;
}
int PartionMid(int array[],int left,int right)
{
    int key=array[right];
    int begin=left;
    int end=right;
    while(begin<end)
    {
        while(begin<end&&array[begin]<=key)begin++;
        while(begin<end&&array[end]>=key)  end--;
        if(begin<end){int mid=array[begin];array[begin]=array[end];array[end]=mid;}
    }
    int mid=array[begin];array[begin]=array[right];array[right]=mid;
    return begin;
}
int MidValue(int a[],int n)
{
    int mid=(n-1)/2;
    int left=0;
    int right=n-1;
    int index=0;
    index=PartionMid(a,left,right);
    while(index!=mid)
    {
        if (index<mid)  index=PartionMid(a,index+1,right);
        else if(index>mid)index=PartionMid(a,left,index-1);
    }
    return a[mid];
}
