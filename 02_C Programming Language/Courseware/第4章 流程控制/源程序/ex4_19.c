/**
����4.19�� ��������һ�����ڻ����2������n���жϸ����Ƿ�Ϊ�����������Ӧ�����
 */

#include <stdio.h>
#include <math.h>

int main(void)
{
    int n, i, k, r;

    do {
        printf("input n:\n");
        scanf("%d", &n);
    } while (n < 2);
    if (n == 2)
        printf("2 is a prime\n");
    else if (n > 2) {
        i = 1;
        k = sqrt(n);
        do {
            ++i;
            r = n % i;
        } while (r && i <= k);
        if(r)
            printf("%d is a prime\n", n);
        else
            printf("%d isn��t a prime\n", n);
    } 	/*  end of else-if  */

    return 0;
}