#include<stdio.h>
#include<string.h>
#define CHANGE 0
int main(void)
{
	int i,k;
    char s[1000];
    gets(s);
    #if CHANGE
    	printf("%s\n",s);
    #else
    	for(i=0;i<strlen(s);i++)
    	{	
			if(s[i]>='a'&&s[i]<='z')
    		printf("%c",s[i]-32);
    		else if(s[i]>='A'&&s[i]<='Z')
    		printf("%c",s[i]+32);
    		else
    		printf("%c",s[i]);
		}
    #endif
    return 0;
} 
