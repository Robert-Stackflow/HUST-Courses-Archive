#include<stdio.h>
int main()
{
    int m,n,x,i,num=0,a[300000],j[n];
    scanf("%d%d",&n,&m);
    x=n;    
    for (i=1;i<=n;i++) {
        a[i]=i;
    }
    int count=0;
    do {
        for (i=1;i<=n;i++) 
		{           
            if (a[i]!=0) 
                num++; 
            if (m==num)
			{
                a[i]=0;
                x--;
                j[count++]=i;
				printf("%d\n",j[count-1]);
				num=0;
            }
        }
    }while(x>0);  
	//printf("%d",j[n-1]); 
    return 0;
}

