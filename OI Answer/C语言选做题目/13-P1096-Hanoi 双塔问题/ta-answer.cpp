#include<cstdio>
using namespace std;
int l,n;
int a[201],b[201];
void gjc()
{
    int t=0;
    for (int j=200;j>0;j--)
     {
         l=b[j]*2+t;
         b[j]=l%10;
         t=l/10;
     }
}
void gjj()
{
    int t=0;
    for (int j=200;j>0;j--)
     {
         l=a[j]+b[j]+t;
         a[j]=l%10;
         t=l/10;
     }
}
int main()
{

    scanf("%d",&n);
    b[200]=1;
    for (int i=1;i<=n;i++)
     {gjc();gjj();}
    int k=1;
    while (a[k]==0&&k<200)
     k++;
    for (int i=k;i<=200;i++)
     printf("%d",a[i]);
     return 0;
}
