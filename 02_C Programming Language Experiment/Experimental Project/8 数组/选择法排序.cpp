#include<stdio.h>

/*****请在下面补充函数 inArray、selectSort 和 outArray 的定义 *****/
void inArray(int arr[],int n);
void selectSort(int arr[],int n);
void outArray(int arr[],int n);
void inArray(int arr[],int n){
	for(int i=0;i<n;i++){
		scanf("%d",&arr[i]);
	}
}
void selectSort(int arr[],int n){
	for(int i=0;i<n-1;i++){
		for(int j=i+1;j<n;j++){
			if(arr[i]>arr[j]){
				int temp=arr[i];
				arr[i]=arr[j];
				arr[j]=temp;
			}
		}
	}
}
void outArray(int arr[],int n){
	for(int i=0;i<=n-1;i++){
		printf("%d ",arr[i]);
	}
}
int main(){
	int arr[100],n;
	printf("请输入数组元素个数：\n");
	scanf("%d",&n);
	inArray(arr,n);
	selectSort(arr,n);
    outArray(arr,n);
    return 0;
}

