/**
����4.4�� ѧ�����Գɼ������±�׼��Ϊ�ĸ��ȼ���xΪѧ�����Է�������
	������Χ				Ӣ�ĵȼ���
	90��x��100			excellent���ţ�
	80��x��90			good������
	60��x��80			middle���У�
	x��60				bad���
����ĳѧ���Ŀ��Է����������ѧ�����Գɼ���Ӣ�ĵȼ���
 */
#include <stdio.h>

int main(void)
{
    float x;

    printf("input the score x( 0 <= x <= 100):\n");
    scanf("%f", &x);
    if ( x > 100 || x < 0)
        printf("input error!\n");
    else if ( x >= 90)
        printf("excellent! \n");
    else if ( x >= 80)
        printf("good! \n");
    else if ( x >= 60)
        printf("middle! \n");
    else printf("bad! \n");

    return 0;
}