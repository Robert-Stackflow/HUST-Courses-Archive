/************************************************************************************
简要描述：模拟猜数的游戏程序
 规则:程序产生一个1到1000之间的随机数让游戏者猜，
      如果猜得不正确,程序会不断地发出信息“Too high”或“Too low”,继续猜直到正确为止，
      输出猜数的次数。
*************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_NUMBER 1000
int GetNum (void);          /*  函数原型   */
void GuessNum(int) ;        /*  函数原型   */

int main(void)
{
	char command;
	int magic;
    printf("This is a guessing game\n\n");
	srand(time(NULL));         /*  用系统时间初始化随机数生成器   */
    do
    {
		magic = GetNum( );    /*   调用GetNum产生随机数供猜测    */
	    GuessNum(magic);    /*    调用GuessNum猜出这个数    */
	    printf("Play again? (Y/N) ");
	    scanf("%1s", &command);     /*   询问是否继续   */
	} while (command == 'y' || command == 'Y');
	return 0;
}

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
函数参数：x表示被猜的数
函数返回值：无
****************************************************************/
void GuessNum(int x)
{
	int guess,counter = 0;
	for (;;)
	{
        printf("guess it: ");
		scanf("%d", &guess);
        counter++;               /*   统计猜的次数   */
		if (guess == x)
		{              /*   猜对    */
			printf("You guessed the number by %d times!\n\n", counter);
            return;
		}
	    else if (guess < x) /*   猜小了   */
	    {
	        printf("Too low. Try again.\n");
	    }
        else                   /*   猜大了   */
        {
            printf("Too high. Try again.\n");
        }
	}
}
