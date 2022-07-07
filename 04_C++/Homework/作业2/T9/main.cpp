#include <algorithm>
#include <cstring>
#include <iostream>
int x = 1;
int y = ::x + 1;
struct A
{
    int x;
    static int y;
    A &operator+=(A &a)
    {
        x += a.x;
        y += a.y;
        return *this;
    }
    operator int() { return x + y; }
    A(int x = ::x + 1, int y = ::y + 10) : x(x) { this->y = y; }
};
int A::y = 100;
int main()
{
    printf("%d %d %d\n", x, y,A::y);
    A a(1, 2), b(3), c;
    printf("x\ty\tA::y\ta.x\ta.y\tb.x\tb.y\tc.x\tc.y\ta\tb\tc\n");
    printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", x, y, A::y, a.x, a.y, b.x, b.y, c.x, c.y, a, b, c);
    int i, *p = &A::y;
    i = b.x + b.y;
    printf("%d\n", i);
    i = *p;
    printf("%d\n", i);
    i = c;
    printf("%d\n", i);
    i = a + c;
    printf("x\ty\tA::y\ta.x\ta.y\tb.x\tb.y\tc.x\tc.y\ta\tb\tc\n");
    printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", x, y, A::y, a.x, a.y, b.x, b.y, c.x, c.y, a, b, c);
    printf("%d\n", i);
    i = b += c;
    printf("x\ty\tA::y\ta.x\ta.y\tb.x\tb.y\tc.x\tc.y\ta\tb\tc\n");
    printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", x, y, A::y, a.x, a.y, b.x, b.y, c.x, c.y, a, b, c);
    printf("%d\n", i);
    i = ((a += c) = b) + 10;
    printf("x\ty\tA::y\ta.x\ta.y\tb.x\tb.y\tc.x\tc.y\ta\tb\tc\n");
    printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", x, y, A::y, a.x, a.y, b.x, b.y, c.x, c.y, a, b, c);
    printf("%d\n", i);
}