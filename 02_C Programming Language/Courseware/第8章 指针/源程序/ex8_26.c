#include "stdio.h"
int main(int argc, char* argv[])
{	int n=0;
    while(n<argc){
		printf("&argv[%d]=%p\t",n,&argv[n]);/*���ָ������Ԫ�صĵ�ַ*/
		printf("argv[%d]=%p\t",n,argv[n]);/*���ָ������Ԫ�ص����ݣ����ַ��������ĵ�ַ*/
		printf("argv[%d]->%s\n",n,argv[n]);/*���ָ������Ԫ��ָ����ַ���*/
		n++;
    }
    return 0;
}
