#include<stdio.h>
#include<stdbool.h>
int main(void)
{
    int n,i,x;
    bool flag=true;      /*flag�����Ʊ��*/
    for(n=6;flag;n++)    /*������̽�ķ���������ֵ̽n�𲽼Ӵ�*/
    {
        for(x=n,i=1;flag&&i<=5;i++)/*�ж��Ƿ���԰�����ĿҪ�����5�η���*/
        {
            if((x-1)%5==0) x=4*(x-1)/5;
            else flag=false;        /*�����ܷ��������ñ��flag=0���˳�����*/
        }
        if(flag) break;         /*��������������������ҵ�����˳���̽����*/
        else flag=true;        /*���������̽��һ����*/
    }
    printf("Total number of fish catched=%d\n",n);
    return 0;
}
