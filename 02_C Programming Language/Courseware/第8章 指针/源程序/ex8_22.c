#include "stdio.h"
void error_prompt(int err_code);
int main(void)
{	int n;
	while(1){
		scanf("%d",&n);
		if(n ==-1)	break;
		error_prompt(n);/*���ݳ����ŵ��ó�����ʾ����*/
	}
	return 0;
}
void error_prompt(int err_code)/*���������ʾ����*/
{	char *perror[]={ /* perror�е�ÿ��Ԫ�ض�ָ���ض��ĳ�����ʾ�ַ����� */
		"can't open file!","read error!",
		"write error!","illegal access exception!"};
	printf("error code:%d :%s\n",err_code,perror[err_code]);/*���ݱ�������ʾ��Ϣ*/
}

