#include<stdio.h>
int main(void)
{
int i=1,sum=0,n,positive=0;
float average;
while (i<=10){
    printf("请输入一个整数"); 
    scanf("%d",&n);
    if (n>0){
        sum=sum+n;
        ++positive;
		++i;
	}
	else
		++i;
    }
    if(positive==0)
    printf("累加和:0\n平均值:0.0");
    else{
		average=(float)sum/positive;
		printf("累加和:%d\n平均值:%.1f",sum,average);
    }
return 0;
} 
