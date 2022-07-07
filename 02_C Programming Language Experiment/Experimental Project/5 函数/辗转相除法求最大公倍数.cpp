#include<stdio.h>
int gcd(int x,int y){		
	int result;
    
	if(x>y)
	{
	    printf("%d %d\n",x,y);
		if(x%y==0)
        {
        	printf("%d %d\n",y,x%y);
            result=y;
            return result;   
        }
        else
		return gcd(y,x%y);
	}
	else
	{
		printf("%d %d\n",x,y);
		if(y%x==0)
        {
        	printf("%d %d\n",x,y%x);
			result=x;
			return result; 
        }
		else	
		return gcd(x,y%x);
	}
}
int main(void)
{
	int x,y;
	scanf("%d%d",&x,&y);
	printf("%d",gcd(x,y));
} 
