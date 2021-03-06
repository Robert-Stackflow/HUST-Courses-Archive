/************************************************************************************
简要描述：	输出斐波那契（FIBONACCI）数列的前60个数。
     FIBONACCI数列是由1和1 开始，之后的数是它前面两数的和，即 1，1，2，3，5，8，……
     由于FIBONACCI数列从大约第45个数起就超过了long类型的范围，
     为避免溢出，应将结果变量说明为long long类型，
*************************************************************************************/
#include <stdio.h>
int main()
{
    long long f1=1, f2=1;
    int i;

    printf("sizeof(long long )=%d\n",sizeof(f1));

    for (i=1; i<=30; i++)
    {
		printf("f(%d)=%I64d\nf(%d)=%I64d\n", (2*i-1), f1, i*2, f2);
		f1=f1+f2;
		f2=f2+f1;
	}
    return 0;
}
