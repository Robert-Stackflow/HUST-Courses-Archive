#include<stdio.h>
int main(void)
{
	int x,i=1,Negative=0,Positive=0,Zero=0;
	while (i<=10) {
		printf("请输入一个整数：");
	    scanf("%d",&x);
		if(x>0){
		    ++Positive;
		}
		else if(x==0){
			++Zero;	
		}
		else{
			++Negative;
		}
		++i;
	}
	printf("在您输入的十个整数中，共有%d个正数，%d个负数，%d个0",Positive,Negative,Zero);
	return 0;
 } 
