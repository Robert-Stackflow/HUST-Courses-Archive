#include<stdio.h>
#include<stdlib.h>
void copy_term(const char * filename);
int main(void)
{
	copy_term("d:\\a.txt");
   return 0;
}
void copy_term(const char * filename)
{
	FILE *fp;
	char ch;
	if ( (fp = fopen(filename,"w") ) == NULL){
		printf("can't open the file!");
		exit(-1);
	}
	while((ch = getchar( ) ) != EOF)   
		fputc(ch,fp);      
	fclose(fp);
}
