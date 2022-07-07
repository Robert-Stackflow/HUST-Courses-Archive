/**
【例4.24】 写一个函数sign，返回浮点数x的符号。如果x小于0，则返回-1；如果x等于0，则返回0；如果x大于0，则返回1。
 */

/*  sign：返回浮点数符号的函数，包含多个带表达式的return语句 */
int sign(double x)
{
    if (x < 0)
        return -1;
    else
        return ((!x) ? 0 : 1);
}