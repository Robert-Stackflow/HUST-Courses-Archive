#include<stdio.h>
void move(int arr[],int n,int k)
{
	int p=n;
	int q=k;
	for(int i=0;i<q;i++)
		arr[p++]=arr[i]; 
	for(int j=0;j<n-k;j++)
		arr[j]=arr[q++];  
	p=n; 
	for(int m=n-k;m<n;m++)
		arr[m]=arr[p++];	
} 

int main(void)
{
	int arr[1000];
	int n,k;
	printf("���������ָ���n:");
	scanf("%d",&n);
	printf("����������:");
	for(int i=0;i<n;i++)
	scanf("%d",&arr[i]);
	printf("������ֶ�����:");
	scanf("%d",&k);
	move(arr,n,k);
	for(int i=0;i<n;i++)
		printf("%d ",arr[i]);
	return 0;
}
