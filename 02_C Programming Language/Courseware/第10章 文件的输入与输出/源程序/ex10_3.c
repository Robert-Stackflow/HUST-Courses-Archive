#include "stdio.h"
int main(void)
{	char a[20];
	unsigned char u,i=0;
	FILE *fin,*fout;	/*�����ļ�ָ��*/
	fout=fopen("c:\\abc.dat","w+");/*�ļ�ָ��foutָ��򿪻򴴽����µ�c�̸�Ŀ¼�µ��ı��ļ�abc.dat*/
	while(gets(a)!=NULL)/*�����ַ����������벻��ctrl+zѭ��*/
		fprintf(fout,"%s",a); /*��a�����ݰ���%s��ʽд���ļ�ָ��foutָ����ı��ļ�abc.dat��*/
	fclose(fout);/*���������ַ�ȫ��ǿ����д��ָ��foutָ����ļ���ȡ��fout����ָ�ļ��Ĺ�ϵ*/
	fin=fopen("c:\\abc.dat","r+b");/*���ն������ļ����·�ʽ��abc.dat�ļ�*/
	while(!feof(fin)){/*��û�е��ļ�β*/
		fread(&u,sizeof(unsigned char),1,fin);/*��finָ����ļ��ж�1���ַ���u��*/
		if(!feof(fin)){/*�ٴ��ж��Ƿ��ļ�β*/
			printf("%04X  %X\t",i++,u);/*���˳��ţ�u���ַ�*/
			if(i%4==0) /*��ʽ���ƣ�ÿ�����4���ַ���Ϣ*/
				printf("\n");/*�������*/
		}
	}
	printf("\n");/*�������*/
	fclose(fin);/*�ر��ļ���ȡ��fin����ָ�ļ��Ĺ�ϵ*/
	return 0;
}
