#include "stdio.h"
#include "stdlib.h"
int main(void)
{	char ch;
	system("dir c:\\");/*ִ����ʾc�̸�Ŀ¼���ļ�����Ŀ¼���ע����"\\"*/
	printf("mycopy.exe is in root directory or not? y/n\n");
	ch=getchar();/*�۲�c�̸�Ŀ¼�Ƿ���mycopy.exe��Ȼ��'y'��'n'*/
	getchar();/*��ch=getchar()��Ļ���*/
	if(ch=='Y'||ch=='y'){
		system("c:\\mycopy.exe");/*ִ����10.5����mycopy.exe*/
		printf("clear screen or not?y/n \n");
		ch=getchar();getchar();/*��ch=getchar()��Ļ���*/
		if(ch=='Y'||ch=='y')
			system("cls");/*ִ�������Ļ����*/
		printf("input any character to finish!\n");
		getchar();/*���������ַ����س���������������*/
	}
	else{/*���c�̸�Ŀ¼��û��mycopy.exe�������ʾ��Ϣ�󷵻ز���ϵͳ*/
		printf("no mycopy.exeprogram in root directory!\n");
		exit(-1);
	}
	return 0;
}
