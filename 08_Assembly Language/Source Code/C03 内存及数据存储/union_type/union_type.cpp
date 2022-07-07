// union_type.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

union test {
    char s[10];
    char c;
    short x;
    int   y;
}temp;
int main()
{
    strcpy(temp.s, "1234567");
    printf(" % x \n", temp.x);
    printf(" % x \n", temp.y);
    printf(" % d \n", temp.c);
    return 0;
}

