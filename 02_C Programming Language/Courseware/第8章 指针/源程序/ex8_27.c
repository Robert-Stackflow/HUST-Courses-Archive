#include "stdio.h"
int main(int num, char* v[])/*��num����argc,��v����argv*/
{	int n=0;	/*����v���ַ�ָ�������������*/
	while(n<num){/*num�������в����ĸ���*/
		printf("&v[%d]=%p\t",n,&v[n]);/*���ָ������Ԫ�صĵ�ַ*/
		printf("&v[%d][0]=%p\t",n,v[n]);/*���Ԫ�ص����ݣ����ַ��������ĵ�ַ*/
		printf("v[%d]=%s\n",n,v[n]);/*���ָ������Ԫ��ָ����ַ���*/
		n++;
  }
  return 0;
}