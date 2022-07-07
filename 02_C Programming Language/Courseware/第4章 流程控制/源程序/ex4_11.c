/**
����4.11�� ����һ��CԴ����(һ������)����ԭ����ʽ������������ƹ�����ɾȥ����Դ���������е�ע�͡�
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
                state = (c == '/') ? START : (putchar(c)��COPY);
            }
            break;
        case COMMENT:
            if (c == '*')
                state = END;
            break;
        case END:
            state = (c == '/') ? COPY : ((c == '*') ? END : COMMENT);
        } 	/*  end of switch��end of while  */

    return 0;
}