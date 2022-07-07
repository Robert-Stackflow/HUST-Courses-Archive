#include<stdio.h> 
int main(void)
{
	int a=1,b=2,c=3,d,e,f,g,h,i,j,k,l=1,m=2,n=3;
	double x=2.0,y=7.7;
	e=(a--?++a:++a);
	d=y+=1/x;
	f=(++a*b--);
	g='a'+'\xa'+l; 
	h=a++;a*=b+1;
	i=a<b&&x==y;
	j=!a+b/c;
	k=(l==-m+n);
	printf("%d;%d;%d;%d;%d;%d;%d;%d", e,d,f,g,a,i,j,k);
}
