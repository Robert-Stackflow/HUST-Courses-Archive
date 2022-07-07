/* 输入一个整数n（n<=10000），
打印n以内所有这样的完全平方数y：y=a2=b2x10+c2。
例如，361=192=62x10+12，则361是这样的完全平方数。*/
/********** Begin **********/
#include<stdio.h>
#include<math.h>
int issquare(int x);
int main(){
	int a,b,c,n,m;
	scanf("%d",&n);
	m=sqrt(n);
	for(a=6;a<=m;a++){
		
		for(c=a-1;c!=0;c--){
			
			if((a+c)*(a-c)%10!=0) continue;
			else{ int x=(a+c)*(a-c)/10;
			        
			      if(issquare(x)){ b=sqrt(x);
				  printf("%d=%d*%d=%d*%d*10+%d*%d\n",a*a,a,a,b,b,c,c);
                  break;
				  }
			}
		}
	}
} 
int issquare(int x){
	if(x == (int)sqrt(x)*(int)sqrt(x))
	return 1;
	else return 0;
}





/**********  End **********/

