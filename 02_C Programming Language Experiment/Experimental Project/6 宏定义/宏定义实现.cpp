#include<stdio.h>
#define  setbits(x,p,n,y)  (x&~(~(~0<< n)<<(p+1-n))|(y&~(~0<<n))<<(p+1-n))
//�����setbits(x,p,n,y)��ȡ������y�����ұ�nλ��
//������Ϊ����x�ӵ�pλ��ʼ������nλ��p����������Ϊ0~15����x������λ���ֲ��䡣
int main(void)
{
	int x, y;
    int p, n;
    scanf("%d%d%d%d", &x,&p,&n,&y);
    printf("%d", setbits(x,p,n,y));
    return 0;
} 
