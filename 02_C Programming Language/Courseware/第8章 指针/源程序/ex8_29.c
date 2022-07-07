#include "stdio.h"
void f1(int x)/*定义有一个整型形参的函数f1*/
{   printf("function f1 is called!\n");
    printf("x=%d\n",x);
}
void f2(int x,int y)/*定义有两个整型形参的函数f2*/
{   printf("function f2 is called!\n");
    printf("x=%d\ty=%d\n",x,y);
}
int main(void)
{   void (*pf1)(int x);/*声明函数指针pf1,所指函数有一个整型形参，无返回值*/
    void (*pf2)(int x,int y);/*声明函数指针pf2,所指函数有两个整型形参，无返回值*/
    pf1=f1;/*使函数指针pf1指向函数f1*/
    pf2=f2;/*使函数指针pf2指向函数f2*/
    pf1(5);/*直接方式：以5为实参，通过函数指针pf1调用函数f1*/
    pf2(10,20);/*直接方式：以10和20为实参，通过函数指针pf2调用函数f2*/
    (*pf1)(50);/*直访方式：以5为实参，通过函数指针pf1调用函数f1*/
    (*pf2)(100,200);/*直访方式：以10和20为实参，通过函数指针pf2调用函数f2*/
    return 0;
}