#include"stdio.h"
#define SIZE 100
#define N 10
void bubble_sort(int * a,int n); 
int main(void)
{
	/**********  Begin  **********/
	int a[SIZE],i,k;
	for(i=0;i<N;i++){
		scanf("%d",&a[i]);
	}
	bubble_sort(a,N);
	for(k=0;k<N;k++){
		printf("%d ",a[k]);	
	}
	/**********   End   **********/
	return 0; 
}
void bubble_sort(int *a,int n)
{
	int i,j,*t;
	for(i=0;i<n-1;i++)
	{
		for(j=0;j<n-i-1;j++)
			if(*(a+j)>*(a+j+1))
				*t=*(a+j),*(a+j)=*(a+j+1),*(a+j+1)=*t;
	}
}
