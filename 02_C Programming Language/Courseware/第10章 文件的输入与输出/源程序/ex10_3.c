#include "stdio.h"
int main(void)
{	char a[20];
	unsigned char u,i=0;
	FILE *fin,*fout;	/*定义文件指针*/
	fout=fopen("c:\\abc.dat","w+");/*文件指针fout指向打开或创建更新的c盘根目录下的文本文件abc.dat*/
	while(gets(a)!=NULL)/*输入字符串，当输入不是ctrl+z循环*/
		fprintf(fout,"%s",a); /*将a中内容按照%s格式写到文件指针fout指向的文本文件abc.dat中*/
	fclose(fout);/*缓冲区中字符全部强制性写到指针fout指向的文件，取消fout与所指文件的关系*/
	fin=fopen("c:\\abc.dat","r+b");/*按照二进制文件更新方式打开abc.dat文件*/
	while(!feof(fin)){/*若没有到文件尾*/
		fread(&u,sizeof(unsigned char),1,fin);/*从fin指向的文件中读1个字符到u中*/
		if(!feof(fin)){/*再次判断是否到文件尾*/
			printf("%04X  %X\t",i++,u);/*输出顺序号，u中字符*/
			if(i%4==0) /*格式控制，每行输出4个字符信息*/
				printf("\n");/*输出换行*/
		}
	}
	printf("\n");/*输出换行*/
	fclose(fin);/*关闭文件，取消fin与所指文件的关系*/
	return 0;
}
