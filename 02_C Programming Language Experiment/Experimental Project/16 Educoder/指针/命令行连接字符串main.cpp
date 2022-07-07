#include<stdio.h>
#include<string.h>
#include<stdlib.h> 
int main(int argc,char* argv[])
{
	int i=0,j=1;
	char *a;
	for(i=1;i<argc;i++)
		i+=strlen(argv[i]);
	a=(char*)malloc(sizeof(char)*i);
	for(i=2;i<argc;i++)
		a=strcat(argv[1],argv[i]);
	p=a; 	
} 
