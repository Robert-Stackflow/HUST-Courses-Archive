#include "stdio.h"
#include "stdlib.h"
char * myfgets(char *s, int n, FILE *stream);
int main(int argc,char *argv[])
{	FILE *fin,*fout;
	int len = atoi(argv[argc-1]);/*将行数字符串转换为整数*/
	int i,j;
	char a[81];
	if((fin = fopen(argv[1],"r")) == NULL){
		printf("can't open the %s file!\n",argv[1]);
		exit(-1);
	}
	for(i = 2; i < argc-1; i++){
		fout = fopen(argv[i],"w");/*打开argv[i]指定的文件进行写操作*/
		j=0;
		while((myfgets(a,80,fin) != NULL) && j++<len)/*从fin中读一行到a中*/
				fputs(a,fout);/*将a中字符串写到fout中*/
		fclose(fout);/*写满len行后关闭文件*/
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
