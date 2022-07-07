/*
用C99的可变参数宏， 更方便地打印调试信息
*/
#include <stdio.h>
#define DEBUG
#ifdef DEBUG
#define msg(fmt, ...) printf(fmt,__VA_ARGS__)
#else
#define msg(fmt,...)
#endif
int main()
{
    printf("hello!\n");
    msg("%s %d %5d\n", "debug1", 10, 20);
    msg("%s %s %10.2f %d\n", "debug2", "test", 10.5, 100);
    return 0;
}


