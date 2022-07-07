#include "stdio.h"
#include "stdlib.h"
void copy_TERM(const char * filename);/*���������뱣�浽�ļ���*/
void type(const char * filename);/*���ļ���������Ļ����ʾ���*/
int main(void)
{	copy_TERM ("c:\\aaa.dat");/*���������뱣�浽aaa.dat��*/
	type("c:\\aaa.dat");/*��aaa.dat����������Ļ����ʾ���*/
	return 0;
}
void copy_TERM (const char * filename)
{	FILE *fp;
	char ch;
	if((fp = fopen(filename,"w")) == NULL){
		printf("can't open the file!");
		exit(-1);
	}
	while((ch = fgetc(stdin)) != EOF) /*��stdin�ж�һ���ַ���������getc*/
		fputc(ch,fp); /*��fpָ����ļ�дһ���ַ���������putc */
	fclose(fp);
}
void type(const char * filename)
{	char ch;
	FILE *fp;
	if((fp = fopen(filename,"r")) == NULL){
		printf("can't open the file!");
		exit(-1);
	}
	while((ch = fgetc(fp)) != EOF) /*��fpָ����ļ��ж�һ���ַ� ������getc */
		fputc(ch,stdout); /*��stdoutָ����ļ�дһ���ַ���������putc */
	fclose(fp);
}
