#include<stdio.h>
#include<string.h>
#include<stdlib.h>
/*ÊäÈëÑùÀı£º
abfg
chgi
cajp
bklg
*/
void strsort(char**s,int size)
{
	char *temp;
	int i,j; 
	for(i=0;i<size-1;i++)
	{
		for(j=0;j<size-i-1;j++)
		{
			if(strcmp(*(s+j),*(s+j+1))>0)
			{ 
				temp=*(s+j);
				*(s+j)=*(s+j+1);
				*(s+j+1)=temp;
			}
		}
	}
}
int main(void)
{
	int i,N;
	char c;
	scanf("%d",&N);
	c=getchar();
	char *s[N],t[50];
	for(i=0;i<N;i++)
	{
		gets(t);
		s[i]=(char *)malloc(strlen(t)+1); 
		strcpy(s[i],t);
	}
	strsort(s,N);
	printf("\n");
	for(i=0;i<N;i++)	puts(s[i]); 
	return 0;
 } 
