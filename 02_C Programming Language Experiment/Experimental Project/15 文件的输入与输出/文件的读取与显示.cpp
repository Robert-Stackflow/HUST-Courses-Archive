#include<stdio.h>
#include<stdlib.h>
void mytype(const char * filename);
int main(void)
{
	mytype ("d:\\a.txt");
	return 0;
}
void mytype(const char * filename)
{
	char ch;
	FILE *fp;
	if((fp = fopen(filename,"r")) == NULL){
		printf("can't open the file!");
		exit(-1);
	}
	while( (ch = fgetc(fp)) != EOF)     		
           putchar (ch);     
	fclose(fp);
} 

