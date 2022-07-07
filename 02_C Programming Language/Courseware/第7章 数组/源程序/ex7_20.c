#include "stdio.h"
#define BASE 10
void itoa(int n,char s[]);
void reverse(char s[]);
int strlen(char s[]);
int main(void)
{
	char s[80];
	int x=12345;
	itoa(x,s);
	printf("%s\n",s);
	return 0;
}
void itoa(int n,char s[])
{	int sign,j=0;
	if((sign=n)<0)
		n=-n;
	while(n>0){
		s[j++]=n%BASE+'0';
		n/=BASE;
	}
	if(sign<0)
		s[j++]='-';
	s[j]= '\0';
	reverse(s);
}
void reverse(char s[])
{	int c,j,k;
	for(j=0,k=strlen(s)-1;j<k;j++,k--)
		c=s[j],s[j]=s[k],s[k]=c;
}
int strlen(char s[])
{	int j=0;
	while(s[j]!= '\0') j++;  /* 可以用while(s[j++])，这样更简洁 */
	return j;
}


