#include<stdio.h> 
void goldbach(int n)
{
	int a,b,i,flag;              
    for(a=2;a<n;a++)
    {
        flag=1;                   
        for(i=2;i<a;i++)
        {
            if(a%i==0)
            {
                flag=0;
                break;
            }
        }
        if(flag==0)  continue;      
        b=n-a;                      
        flag=1;                     
        for(i=2;i<b;i++)           
        {
            if(b%i==0)
            {
                flag=0;
                break;
            }
        }                         
        if(flag==1)                 
        {
            printf("%d=%d+%d",n,a,b);
            return;
        }
    }
} 
int main(void)
{
	int n;
	while(scanf("%d",&n)!=EOF) 
			goldbach(n);
	return 0;
}
