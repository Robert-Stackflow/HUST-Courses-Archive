#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#define max(a,b) (a > b ? a : b)
char s0[10088];
int s1[10088],s2[10088],s[10088];
int main()
{
	int i,j,l1,l2,l,end;
	
	scanf("%s",s0);
	l = strlen(s0);
	for(i = l - 1,j = 0;i >= 0;j++,i--)
	s1[j] = s0[i] - '0';
	l1 = j;
	scanf("%s",s0);
	l = strlen(s0);
	for(i = l - 1,j = 0;i >= 0;j++,i--)
	s2[j] = s0[i] - '0';
	l2 = j;
	
	if(s1[0]==0 || s2[0] == 0)
	{
		printf("0");
		return 0;
	}
	for(i = 0;i < l2;i++)
	{
		for(j = 0;j < l1;j++)
		{
			s[i + j] += s2[i] * s1[j];
			s[i + j + 1] += s[i + j] / 10;
			s[i + j] %= 10; 
		}
	}
	for(i = l1 + l2;s[i] == 0;i--)
    ;
    while(i >= 0)
    printf("%d",s[i--]);
}
