#include <cstdio>
#include <iostream>
struct A
{
    int i;
    A(int v)
    {
        i = v;
        printf("A(%d) ", i);
    }
    A(const A &a)
    {
        i = a.i;
        printf("A(A&) ");
    }
    ~A() { printf("~A(%d) ", i); }
    operator int() const
    {
        printf("int() ");
        return i;
    }
    A &operator=(const A &a)
    {
        printf("=() ");
        i = a.i;
        return *this;
    }
};
int main(void)
{
    printf("A x = 1;\t\t");
    A x = 1;
    printf("\n");

    printf("x = 1;\t\t\t");
    x = 1;
    printf("\n");

    printf("A y = x;\t\t");
    A y = x;
    printf("\n");

    printf("y = x;\t\t\t");
    y = x;
    printf("\n");

    printf("x = 1 + x;\t\t");
    x = 1 + x;
    printf("\n");

    printf("A z(x + y);\t\t");
    A z(x + y);
    printf("\n");

    printf("printf\t\t\t");
    printf(" %d %d", y, (int)y);
    // printf("\n");
}
