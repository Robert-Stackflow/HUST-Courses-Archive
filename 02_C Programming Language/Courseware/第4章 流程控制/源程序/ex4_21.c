/**
����4.21�� �ھ���2��3��Ԫ�ص������а��в��ҵ�һ��ֵΪ-1��Ԫ�ء�
 */

#include <stdio.h>

int main(void)
{
    int i, j, a[2][3];

    printf("input a 2��3 array:\n");
    for (i=0; i<2; ++i)
        for (j=0; j<3; ++j)
            scanf("%d", &a[i][j]);

    for (i = 0; i < 2; ++i)  /* ������a���ҵ�һ��ֵΪ-1��Ԫ�� */
        for (j = 0; j < 3; ++j)
            if (a[i][j] == -1) goto found;
nofound:
    printf("not found!\n");
    goto end;
found:
    printf("found one is��a[%d][%d]\n", i, j);

end:
    return 0;
}