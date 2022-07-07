/* ��putchar��ʵ�ֺ���printf�Ĺ��� */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

int myprintf(char *fmt, ...);

int main()
{
    int m;                                 /* �������ַ�����Ŀ */
    m = myprintf("%c\t%d\t%s\t%f\t%lf\n", 65, 65, "65", 65.f, 65.);
    myprintf("%d\n", m);
    m = printf("%c\t%d\t%s\t%f\t%lf\n", 65, 65, "65", 65.f, 65.);
    printf("%d\n", m);    /* ��ͬ����ʵ�ε���printf����������Ƚ� */
    return 0;
}

int myprintf(char *fmt, ...)
{
    va_list ap;                           /* ��һ��������va_list���͵Ķ���ap */
    char cval, *pch;            /* cval����ַ��Ϳɱ������pch���ڽ�����ʽ�� */
    char *sval;    /* ����ָ���ַ������͵Ŀɱ����,������ָ��ת������ַ��� */
    char cvt[320];  /* �������ת������ַ�����˫���ȸ������ִ��Լ310λ */
    int ival, m, n;               /* ival������Ϳɱ������m, n���ں���fcvt�� */
    double dval;                           /* dval���˫���ȸ����Ϳɱ���� */
    int cnt = 0;                       /* cnt�������������������ַ��ĸ��� */

    va_start(ap, fmt);   /* �ڶ�������ʼ��ap��ʹ��ָ�����������fmt����λ�� */
    for (pch=fmt; *pch; pch++) {       /* ������ʽ�ַ�����������βʱ����ѭ�� */
        if (*pch != '%') {                               /* ��%�ַ�ԭ����� */
            putchar(*pch);
            cnt++;
            continue;          /* ���ӿɱ������ȡ���ݣ�ֱ�ӽ�����һ��ѭ�� */
        }
        /* pchָ��%ʱ���жϺ����ַ����������ִ�е��������ӿɱ������ȡ���� */
        switch (*++pch) {            /* ʹpchָ������ַ������жϺ����ַ���ֵ */
        case 'c':                                            /* ����ת��˵��%c */
            cval = va_arg(ap, int);      /* �ӿɱ������ȡһ��int�Ͳ�������Ϊ�ַ��� */
            putchar(cval);
            cnt++;
            break;
        case 'd':                                             /* ����ת��˵��%d */
            ival = va_arg(ap, int);                 /* �ӿɱ������ȡһ��int�Ͳ��� */
            itoa(ival, cvt, 10);       /* ����int������ת��Ϊʮ�������ִ�������cvt */
            for (sval=cvt; *sval; sval++,cnt++)
                putchar(*sval);            /* �������cvt�е������ַ���ֱ����β */
            break;
        case 's':                                             /* ����ת��˵��%s */
            for (sval=va_arg(ap, char *); *sval; sval++,cnt++)
                putchar(*sval);      /* �ӿɱ������ȡ�ַ�ָ�룬��svalָ����� */
            break;
        case 'l':                                       /* �п��ܹ���ת��˵��%lf */
            if (*(pch+1) != 'f') {                                /* �����ַ���Ϊf */
                putchar(*--pch);                        /* pch���ˣ�ָ�����% */
                cnt++;
                break;
            }
            pch++;           /* �����ַ�Ϊfʱ������ת��˵��%lf����������ִ�� */
        case 'f':                          /* ����ת��˵��%f����%lf�ڴ�������ͬ */
            dval = va_arg(ap, double);              /* �ӿɱ������ȡdouble������ */
            sval = fcvt(dval, 6, &m, &n);          /* ת��Ϊ�������ִ���6��С��λ */
            if (n) {  /* n=1������������Ϊ�����������-��n=0ʱΪ������������� */
                putchar('-');
                cnt++;
            }
            if (m <= 0) {     /* m<0��С����������|m|λλ�ã�m=0��С�����ڴ��� */
                int i;
                cnt += strlen(sval) + 2 - m; /* �������������������������ִ����� */
                putchar('0');              /* ��Ϊ��������Ϊ0���������ǰ����0. */
                putchar('.');
                for (i=0; i<-m; i++)           /* �����sval�����ִ�ǰ��������0 */
                    putchar('0');
            }
            else {                     /* ����m>0��С�����ڴ�������mλλ�� */
                int i;
                cnt += strlen(sval) + 1;/* �������ֲ�Ϊ0ʱ����������һ��С����. */
                for (i=0; i<m; i++)                             /* ����������� */
                    putchar(*sval++);
                putchar('.');                                     /* ���С���� */
            }
            while (*sval)                                      /* ���ʣ�ಿ�� */
                putchar(*sval++);
            break;
        default:                                /* û�й��ɸ���������ת��˵�� */
            putchar(*--pch);                                /* ָ����ˣ����% */
            cnt++;
            break;
        }
    }
    va_end(ap);                       /* ���Ĳ��������ֳ���ʹ�����ܹ���ȷ���� */

    return cnt;                                          /* ��������ַ��ĸ��� */
}