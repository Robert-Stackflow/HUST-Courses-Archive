#include "stdio.h"
#include "stdlib.h"
char * myfgets(char *s, int n, FILE *stream);
int main(int argc,char *argv[])
{	FILE *fin,*fout;
	int len = atoi(argv[argc-1]);/*�������ַ���ת��Ϊ����*/
	int i,j;
	char a[81];
	if((fin = fopen(argv[1],"r")) == NULL){
		printf("can't open the %s file!\n",argv[1]);
		exit(-1);
	}
	for(i = 2; i < argc-1; i++){
		fout = fopen(argv[i],"w");/*��argv[i]ָ�����ļ�����д����*/
		j=0;
		while((myfgets(a,80,fin) != NULL) && j++<len)/*��fin�ж�һ�е�a��*/
				fputs(a,fout);/*��a���ַ���д��fout��*/
		fclose(fout);/*д��len�к�ر��ļ�*/
	}
	fclose(fin);
	return 0;
}
char * myfgets(char *s, int n, FILE *stream)
{	int c=0;
	char *p=s;
	while(c != '\n' && n-- > 0 && (c = getc(stream)) != EOF)
		*p++=c;
	if(c == EOF && p == s)
		return NULL;
	*p=0;
	return ((ferror(stream)) ? NULL : s);
}
