#include<stdio.h>
int main(void)
{
int i=1,sum=0,n,positive=0;
float average;
while (i<=10){
    printf("������һ������"); 
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
    printf("�ۼӺ�:0\nƽ��ֵ:0.0");
    else{
		average=(float)sum/positive;
		printf("�ۼӺ�:%d\nƽ��ֵ:%.1f",sum,average);
    }
return 0;
} 
