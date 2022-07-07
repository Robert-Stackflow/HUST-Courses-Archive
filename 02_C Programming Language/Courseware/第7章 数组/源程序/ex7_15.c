#include "stdio.h"
int strstr(char cs[], char ct[]);
int strlen(char s[]);
int main(void)
{
	char s[]="they are workers.you are students.",c[]="are";
	printf("j=%d\n",strstr(s,c));
	return 0;
}
int strstr(char cs[], char ct[])
{	int j=0,k;
	for(;cs[j]!= '\0';j++)
		if(cs[j]==ct[0] ){
			k=1;
			while(cs[j+k]==ct[k] && ct[k]!= '\0')
				k++;
				if(k==strlen(ct)) 
					return j;
		}
	return -1;
}
int strlen(char s[])
{	int j=0;
	while(s[j]!= '\0') j++;  /* 可以用while(s[j++])，这样更简洁 */
	return j;
}