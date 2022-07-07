#include<stdio.h> 
int x;
int facto();
int main()
{
    int x;
    scanf("%d",&x);
    printf("%d",facto());
}
int facto()
{
     if(x==0||x==1)
        return(1);
      else if(x<0)
        printf("!");
      else if(x>1)
        return (x*facto(x-1));
}
