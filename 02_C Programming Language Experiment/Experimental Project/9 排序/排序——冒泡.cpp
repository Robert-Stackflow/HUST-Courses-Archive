#include<stdio.h>
#include<string.h>
//#include<myfunction.h>
#define order >//请改变符号以实现升序和降序 
void bubble_sort(int b[]){
	int s;
	printf("请输入整数个数："); 
	scanf("%d",&s);
	for(int i=0;i<s;i++)
		scanf("%d",&b[i]);
	int i,j,t;
	for (i=0;i<s-1;i++){
	for(j=0;j<s-i-1;j++)
		if(b[j] order b[j+1])
			t=b[j],b[j]=b[j+1],b[j+1]=t;
	printf("\n第%d次排序得到:",i+1);
	for(int i=0;i<s;i++)
		printf("%d ",b[i]);
		printf("\n");	
}
}
int main(void){
	int x[1000];
	char str3[]="luck\0ily";
	char str2[]={'i','\0','l','y'};
	char str1[]={'l','u','c','k',0,'m'};
	printf("%s\n",str1);
	puts(str1);
	printf("%s\n",str2);
	printf("%s\n",str3);
	printf("%d\n",strlen(str3));
	//bubble_sort(x);
	return 0;
}
