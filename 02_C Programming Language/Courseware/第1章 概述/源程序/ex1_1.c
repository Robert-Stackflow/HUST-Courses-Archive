#include "stdio.h"				/*�ļ���������Ԥ��������*/
void show(char str[]);				/*����ԭ��˵�����*/
int main(void)					/*������*/
{						/*�����忪ʼ*/
	  char name[20];			/*�������*/
	  printf("Input your name please!\n");	/*���һ����ʾ��Ϣ*/
	  gets(name);				/*��ȡ�û��Ӽ�������һ���ַ���*/
	  printf("Hello %s!\n",name);		/*���Hello���û���*/
	  show(name);				/*����show����������תshow ִ��*/
	  return 0;				/*����*/
}						/*���������*/
void show(char str[])				/*show������ͷ��*/
{						/*�����忪ʼ*/
	  printf("This is the first program \
for %s to learn C programming!\n",str); /*����β��"\"�����б�־*/
}						/* ���������*/
