
#include <stdio.h>

int f(int x, int y)
{
    int r = 1;

    while (y > 1) {
        if (y % 2 == 1) {
            r = x * r;
        }
        x = x * x;
        y = y / 2;

    }

    return r * x;
}

int main()
{
    int x, y;

    printf("input two integers:\n");
    while (scanf("%d %d", &x, &y) == 2) {
        printf("f(%d, %d) = %d\n", x, y, f(x, y));
        printf("input two integers:\n");
    }

    return 0;
}
