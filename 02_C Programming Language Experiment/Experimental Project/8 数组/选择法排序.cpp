#include<stdio.h>

/*****�������油�亯�� inArray��selectSort �� outArray �Ķ��� *****/
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
	printf("����������Ԫ�ظ�����\n");
	scanf("%d",&n);
	inArray(arr,n);
	selectSort(arr,n);
    outArray(arr,n);
    return 0;
}

