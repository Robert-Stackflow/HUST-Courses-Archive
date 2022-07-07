#include "stdio.h"
#include "stdlib.h"
int main(int argc, char* argv[])
{	int ch;
	if(argc!=3){/*�����в�����Ŀ������3��˵�������и�ʽ����*/
		printf("Arguments error!\n");
		exit(-1);
	}
	if(freopen(argv[1],"r",stdin)==NULL){ /* stdinָ��source_file */
		printf("Can't open %s file!\n",argv[1]);
		exit(-1);
	}
	freopen(argv[2],"w",stdout); /* ʹstdoutָ��target_file */
	while((ch=getchar())!=EOF) /* ��source_file�ж��ַ� */
		putchar(ch); /* ��target_file��д�ַ���ʵ�ֿ������� */
	fclose(stdin); /* �ر�source_file */
	fclose(stdout); /* �ر�target_file */
	return 0;
}
