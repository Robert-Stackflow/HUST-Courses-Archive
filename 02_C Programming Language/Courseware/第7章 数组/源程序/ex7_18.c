#include "stdio.h"
void reverse(char s[]);
int strlen(char s[]);
int main(void)
{
	char s[]=".ekal eht no taob a si ereht";
	reverse(s);
	printf("%s\n",s);
	return 0;
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

