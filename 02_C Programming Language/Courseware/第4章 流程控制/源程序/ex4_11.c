/**
【例4.11】 输入一个C源程序(一段正文)，按原来格式复制输出，复制过程中删去输入源程序中所有的注释。
 */

#include <stdio.h>

enum {COPY, START, COMMENT, END};

/*  remove comments from c program  */
int main(void)
{
    char c;
    int state = COPY;

    printf("input C program end with ctrl+z:\n");
    while ((c=getchar()) != EOF)
        switch (state) {
        case COPY:
            if (c == '/') 
                state = START;
            else
                putchar(c);
            break;
        case START:
            if (c == '*')
                state = COMMENT;
            else {
                putchar('/');
                state = (c == '/') ? START : (putchar(c)，COPY);
            }
            break;
        case COMMENT:
            if (c == '*')
                state = END;
            break;
        case END:
            state = (c == '/') ? COPY : ((c == '*') ? END : COMMENT);
        } 	/*  end of switch，end of while  */

    return 0;
}