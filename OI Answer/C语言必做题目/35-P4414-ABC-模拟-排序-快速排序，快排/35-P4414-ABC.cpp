#include<stdio.h>
#include<math.h>
int main(void)
{
	int a[3],temp,b[3];
	char le[3];
	for(int i=0;i<3;i++)scanf("%d",&a[i]);
	scanf("%s",le);
	for(int i=0;i<2;++i)
        for(int j=i+1;j<3;++j)
            if(a[i]>a[j])
                temp=a[i],a[i]=a[j],a[j]=temp;
	for(int i=0;i<3;i++)
	{
		if(le[i]=='A') b[i]=a[0];
		else if(le[i]=='B') b[i]=a[1];
		else b[i]=a[2];
	}
	for(int i=0;i<3;i++) printf("%d ",b[i]);
}
