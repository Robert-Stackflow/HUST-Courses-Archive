#include"stdio.h"
#define SIZE 100
void reverseOrder(int a[ ],int n);
int main()
{
	int n,i;
	int arr[SIZE];
	scanf("%d",&n);
	for(i=0;i<n;i++){
		scanf("%d",&arr[i]); 
	}
	reverseOrder(arr,n);
	for(i=0;i<n;i++){
		printf("%d ",arr[i]); 
	} 
	return 0;
}
void reverseOrder(int a[],int n)
{
	int i=0;
	for(i=0;i<(n/2);i++)
	{
		int t=0;
		t=*(a+n-i-1); 
		*(a+n-i-1)=*(a+i);
		*(a+i)=t;
		//为何改变交换顺序就发生错误？ 
	}
}

