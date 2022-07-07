#include "stdio.h"
#include "fcntl.h"
#include "io.h"
#include "stdlib.h"
/* û�а���stat.h���Լ�����S_IREAD ��S_IWRITE */
#define S_IREAD	0x0100	/* ֻ����ʽ */
#define S_IWRITE  0x0080	/*ֻд��ʽ*/
#define BUF_SIZE  512 /* �����СΪ512�ֽ� */
int main(int argc,char *argv[])
{	int in,out,num,i;
	unsigned char s[BUF_SIZE];
	if((in = open(argv[1],O_RDONLY)) == -1){/* ��ֻ����ʽ��Դ�ļ�*/
		printf("open source file failed!\n");
		exit(-1);
	} /* �����Զ�д��ʽ��Ŀ���ļ� */
	if((out = creat(argv[2],S_IREAD | S_IWRITE)) == -1){
		printf("create target file failed!\n");
		exit(-1);
	}
	while((num = read(in,s,BUF_SIZE))>0){ /* ��Դ�ļ� */
		if(write(out,s,num) != num){ /* дĿ���ļ� */
			printf("write error on %s\n",argv[2]);
			exit(-1);
		}
	}
	close(in); /* �ر�Դ�ļ� */
	close(out); /* �ر�Ŀ���ļ� */
	in = open(argv[2],O_RDONLY); /* ���´��ѿ����ļ� */
	while((num = read(in,s,BUF_SIZE))>0){ /* ���ѿ����ļ� */
		i=0;
		while(i<=num) /* ѭ������Ѷ����num ���ַ� */
			putchar(s[i++]);
	}
	putchar('\n');
	close(in); 
	return 0;
}
