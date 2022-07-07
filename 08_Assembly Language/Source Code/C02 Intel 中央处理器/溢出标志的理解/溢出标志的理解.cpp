#include <stdio.h>
int main()
{
    short   x, y, z;
    x = 32766;     // 7FFEH
    y = 3;
    z = x + y;
    printf("%d %d %d \n", x, y, z);
    return 0;
}
