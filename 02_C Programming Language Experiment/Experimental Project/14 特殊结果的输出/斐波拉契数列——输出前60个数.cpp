#include <stdio.h>
 
int main()
{
    unsigned long long  t1 = 0, t2 = 1, nextTerm = 0, n=3;
    printf("斐波那契数列第1个数:%llu\n", t2);
    nextTerm = t1 + t2;
    while(n <= 101)
    {
        printf("斐波那契数列第%llu个数:%llu\n",n-1,nextTerm);
        t1 = t2;
        t2 = nextTerm;
        nextTerm = t1 + t2;
        ++n;
    }
    return 0;
}
