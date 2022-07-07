#include <stdio.h>  
#include <math.h>
 
int main(){     
	int m,n;
	scanf("%d %d",&m,&n);
	int plus;
	plus=m%n;
	int  x;
	x=m*n;
	
	if(plus==0){
		printf("%d %d",n,x/n);
	}else{
		
		while(plus!=0){
			m=n;
			n=plus;
			plus=m%n;		 
		}
		printf("%d %d",n,x/n);
	}					         
    return 0;  
 } 

