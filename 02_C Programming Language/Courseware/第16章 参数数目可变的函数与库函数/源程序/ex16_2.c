/* 用putchar来实现函数printf的功能 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

int myprintf(char *fmt, ...);

int main()
{
    int m;                                 /* 存放输出字符的数目 */
    m = myprintf("%c\t%d\t%s\t%f\t%lf\n", 65, 65, "65", 65.f, 65.);
    myprintf("%d\n", m);
    m = printf("%c\t%d\t%s\t%f\t%lf\n", 65, 65, "65", 65.f, 65.);
    printf("%d\n", m);    /* 用同样的实参调用printf，用作输出比较 */
    return 0;
}

int myprintf(char *fmt, ...)
{
    va_list ap;                           /* 第一步，定义va_list类型的对象ap */
    char cval, *pch;            /* cval存放字符型可变参数，pch用于解析格式串 */
    char *sval;    /* 用于指向字符串类型的可变参数,兼用于指向转换后的字符串 */
    char cvt[320];  /* 用来存放转换后的字符串，双精度浮点数字串最长约310位 */
    int ival, m, n;               /* ival存放整型可变参数，m, n用于函数fcvt中 */
    double dval;                           /* dval存放双精度浮点型可变参数 */
    int cnt = 0;                       /* cnt用作计数器，存放输出字符的个数 */

    va_start(ap, fmt);   /* 第二步，初始化ap，使其指向参数区参数fmt后面位置 */
    for (pch=fmt; *pch; pch++) {       /* 解析格式字符串，遇到串尾时结束循环 */
        if (*pch != '%') {                               /* 非%字符原样输出 */
            putchar(*pch);
            cnt++;
            continue;          /* 不从可变参数区取数据，直接进入下一轮循环 */
        }
        /* pch指向%时，判断后续字符，根据情况执行第三步，从可变参数区取数据 */
        switch (*++pch) {            /* 使pch指向后续字符，并判断后续字符的值 */
        case 'c':                                            /* 构成转换说明%c */
            cval = va_arg(ap, int);      /* 从可变参数区取一个int型参数，作为字符码 */
            putchar(cval);
            cnt++;
            break;
        case 'd':                                             /* 构成转换说明%d */
            ival = va_arg(ap, int);                 /* 从可变参数区取一个int型参数 */
            itoa(ival, cvt, 10);       /* 将该int型数据转换为十进制数字串，存入cvt */
            for (sval=cvt; *sval; sval++,cnt++)
                putchar(*sval);            /* 依次输出cvt中的数字字符，直到串尾 */
            break;
        case 's':                                             /* 构成转换说明%s */
            for (sval=va_arg(ap, char *); *sval; sval++,cnt++)
                putchar(*sval);      /* 从可变参数区取字符指针，用sval指向并输出 */
            break;
        case 'l':                                       /* 有可能构成转换说明%lf */
            if (*(pch+1) != 'f') {                                /* 后续字符不为f */
                putchar(*--pch);                        /* pch回退，指向并输出% */
                cnt++;
                break;
            }
            pch++;           /* 后续字符为f时，构成转换说明%lf，接着往下执行 */
        case 'f':                          /* 构成转换说明%f，与%lf在处理上相同 */
            dval = va_arg(ap, double);              /* 从可变参数区取double型数据 */
            sval = fcvt(dval, 6, &m, &n);          /* 转换为浮点数字串，6个小数位 */
            if (n) {  /* n=1，表明浮点数为负，输出符号-；n=0时为正，不输出符号 */
                putchar('-');
                cnt++;
            }
            if (m <= 0) {     /* m<0，小数点在左移|m|位位置；m=0，小数点在串首 */
                int i;
                cnt += strlen(sval) + 2 - m; /* 计算这两种情况下输出浮点数字串长度 */
                putchar('0');              /* 因为整数部分为0，所以输出前导串0. */
                putchar('.');
                for (i=0; i<-m; i++)           /* 在输出sval中数字串前补齐数字0 */
                    putchar('0');
            }
            else {                     /* 否则m>0，小数点在串首往右m位位置 */
                int i;
                cnt += strlen(sval) + 1;/* 整数部分不为0时，输出串多出一个小数点. */
                for (i=0; i<m; i++)                             /* 输出整数部分 */
                    putchar(*sval++);
                putchar('.');                                     /* 输出小数点 */
            }
            while (*sval)                                      /* 输出剩余部分 */
                putchar(*sval++);
            break;
        default:                                /* 没有构成给定的五种转换说明 */
            putchar(*--pch);                                /* 指针回退，输出% */
            cnt++;
            break;
        }
    }
    va_end(ap);                       /* 第四部，清理现场，使函数能够正确返回 */

    return cnt;                                          /* 返回输出字符的个数 */
}