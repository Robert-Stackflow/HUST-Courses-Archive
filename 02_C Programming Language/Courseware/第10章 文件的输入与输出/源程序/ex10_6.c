#include "stdio.h"
#include "stdlib.h"
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
		while((fgets(a,80,fin) != NULL) && j++<len)/*��fin�ж�һ�е�a��*/
				fputs(a,fout);/*��a���ַ���д��fout��*/
		fclose(fout);/*д��len�к�ر��ļ�*/
	}
	fclose(fin);
	return 0;
}
