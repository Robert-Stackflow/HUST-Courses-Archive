#include<stdio.h>
#include<math.h>
int m,n,k,l,d,x,y,p,q,line[1010],row[1010],checkl[1010],checkr[1010];
void sort(int*s,int flag,int*check,int range);
int main(void)
{

    scanf("%d%d%d%d%d",&m,&n,&k,&l,&d);
    for(int i=0;i<d;i++)
    {
        scanf("%d%d%d%d",&x,&y,&p,&q);
        if(x==p) {if(y<q) row[y]++;else row[q]++;}
        else    {if(x<p) line[x]++;else line[p]++;}
    }
    sort(line,k,checkl,m);
    sort(row,l,checkr,n);
    for(int i=0;i<1001;i++)
        if(checkl[i]) printf("%d ",i);
    printf("\n");
    for(int i=0;i<1001;i++)
        if(checkr[i]) printf("%d ",i);
//    system("PAUSE");
}
void sort(int*s,int flag,int*check,int range)
{
    for(int i=1;i<=flag;i++)
    {
        int max=0,sign;
        for(int j=1;j<range;j++)
        {
            if(s[j]>max)
            {
                max=s[j];
                sign=j;
            }
        }
        s[sign]=0;
        check[sign]=1;
    }
}
