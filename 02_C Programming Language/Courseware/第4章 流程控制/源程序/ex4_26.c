/**
����4.26�� ����һ����ĸ������Ļ��������������ĸ������߶ȵ��ַ�"������"����������Сд��ĸd��������������ͼ�Σ���������д��ĸD��������ұ�ͼ�Ρ�
 */

#include <stdio.h>
#include <ctype.h>

int main(void)
{
    char c, c1, c2, top;
    int i;

    printf("input a character:\n");
    top = isupper(c = getchar()) ? 'A' : (islower(c) ? 'a' : '\0');
    if (top) {
        for (c1=top; c1<=c; ++c1){
            for (i=1; i<=40-2*(c1-top); ++i)
                putchar(' ');
            for (c2=top; c2<=c1; ++c2)
                printf("%2c", c2);
            for (c2=c1�C1; c2>=top; --c2)
                printf("%2c", c2);
            printf("\n");
        } 	/*  end of external for  */
    } 	/*  end of if  */

    return 0;
}