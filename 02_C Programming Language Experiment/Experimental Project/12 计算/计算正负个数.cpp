#include<stdio.h>
int main(void)
{
	int x,i=1,Negative=0,Positive=0,Zero=0;
	while (i<=10) {
		printf("������һ��������");
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
	printf("���������ʮ�������У�����%d��������%d��������%d��0",Positive,Negative,Zero);
	return 0;
 } 
