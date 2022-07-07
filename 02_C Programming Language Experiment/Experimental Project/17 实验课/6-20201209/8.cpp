#include<stdio.h> 
#include<string.h>
int delSubstr(char *str,char *substr);
int main(void)
{
	char str[100],substr[100];
	gets(str);
	gets(substr);
	int flag=delSubstr(str,substr);
	printf("%s",str);
	if(flag) printf("\n1");
	else 	printf("\n0");
}


int delSubstr(char *str,char *substr)
{
	char mid[100];
	char *p;
	if(strstr(str,substr))
	{
		while((p=strstr(str,substr))!=NULL)
		{
		*p='\0';
		strcpy (mid,p+strlen(substr)); 
		strcat(str,mid);
		}
		return 1;
	}
	else return 0;
}
