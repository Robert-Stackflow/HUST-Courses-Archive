/************************************************************************************
 简要描述：猜数程序的特别版本，把magic定义为外部变量,将程序放在两个文件中。
           这是第2文件ex5_6_2.c: 包含GetNum 和GuessNum函数的定义
*************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#define MAX_NUMBER 1000
extern int magic;  /*  外部变量magic的声明   */
/****************************************************************
函数名称：GetNum
函数功能：产生一个1到MAX_NUMBER之间的随机数,供游戏者猜测。
函数参数：无
函数返回值：返回产生的随机数
*****************************************************************/
int GetNum(void)     /*  等价于 GetNum( )    */
{
	printf("A magic number between 1 and %d has been chosen.\n",MAX_NUMBER);
	return (rand() % MAX_NUMBER + 1);
}

/****************************************************************
函数名称：GuessNum
函数功能：游戏者根据提示反复猜数，直至猜对为止，输出猜数的次数。
函数参数：无
函数返回值：无
备注：函数间利用外部变量magic传递信息
****************************************************************/
void GuessNum ( )
{
	int guess,counter = 0;
	for (;;)
	{
        printf("guess it: ");
		scanf("%d", &guess);
        counter++;               /*   统计猜的次数   */
		if (guess == magic)
		{              /*   猜对    */
			printf("You guessed the number by %d times!\n\n", counter);
            return;
		}
	    else if (guess < magic)            /*   猜小了   */
		    printf("Too low. Try again.\n");
        else                   /*   猜大了   */
            printf("Too high. Try again.\n");
	}

}

