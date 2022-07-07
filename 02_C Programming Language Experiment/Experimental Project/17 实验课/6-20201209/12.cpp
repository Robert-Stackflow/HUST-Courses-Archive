#include<stdio.h>
#include<string.h>
void  task0()
{
    printf("task0  is  called!\n");
}
void  task1()
{
    printf("task1  is  called!\n");
}
void  task2()
{
    printf("task2  is  called!\n");
}
void  task3()
{
    printf("task3  is  called!\n");
}
void  task4()
{
    printf("task4  is  called!\n");
}
void  task5()
{
    printf("task5  is  called!\n");
}
void  task6()
{
    printf("task6  is  called!\n");
}
void  task7()
{
    printf("task7  is  called!\n");
}
void  execute(void  (*a[])(),int  n)
{
    int  i;
    for(i=0;i<n;i++)
        (*a[i])();
}
void  scheduler(char  *s)
{
    int  count,i;
    char  c;
    count=strlen(s);
	void  (*f[8])(void);
    f[0]=task0;
    f[1]=task1;
    f[2]=task2;
    f[3]=task3;
    f[4]=task4;
    f[5]=task5;
	f[6]=task6;
    f[7]=task7;
    void  (*a[count])();
    for(i=0;i<count;i++)
    {
        c=*(s+i);
        a[i]=f[c-'0'];
    }
    execute(a,count);
}
int main(void)
{
    char str[30];
    scanf("%s",str);
    scheduler(str);
    return  0;
}

