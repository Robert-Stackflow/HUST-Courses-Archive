#include "stdio.h"
#include "stdlib.h"
void copy_TERM(const char * filename);/*将键盘输入保存到文件中*/
void type(const char * filename);/*将文件内容在屏幕上显示输出*/
int main(void)
{	copy_TERM ("c:\\aaa.dat");/*将键盘输入保存到aaa.dat中*/
	type("c:\\aaa.dat");/*将aaa.dat的内容在屏幕上显示输出*/
	return 0;
}
void copy_TERM (const char * filename)
{	FILE *fp;
	char ch;
	if((fp = fopen(filename,"w")) == NULL){
		printf("can't open the file!");
		exit(-1);
	}
	while((ch = fgetc(stdin)) != EOF) /*从stdin中读一个字符，可以用getc*/
		fputc(ch,fp); /*向fp指向的文件写一个字符，可以用putc */
	fclose(fp);
}
void type(const char * filename)
{	char ch;
	FILE *fp;
	if((fp = fopen(filename,"r")) == NULL){
		printf("can't open the file!");
		exit(-1);
	}
	while((ch = fgetc(fp)) != EOF) /*从fp指向的文件中读一个字符 可以用getc */
		fputc(ch,stdout); /*向stdout指向的文件写一个字符，可以用putc */
	fclose(fp);
}
