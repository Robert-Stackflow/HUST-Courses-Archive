#include <stdio.h>
#include <stdlib.h>

int main()
{
    int age;
    printf("����������:");
    scanf("%d",&age);
    if(age=0)   
	/*��Ϊage=xʱ��xΪ����ֵ�����Ϊ���ԣ�
	����xΪ0ʱ���Ϊ�����ԣ�ע�����Ϊ==*/
        printf("����������\n");
    else printf("������������\n");
    return 0;
}
