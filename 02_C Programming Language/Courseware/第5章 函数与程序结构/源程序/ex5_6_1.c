/************************************************************************************
 简要描述：猜数程序的特别版本，把magic定义为外部变量,将程序放在两个文件中。
           这是第1文件ex5_6_1.c: 包含外部变量magic和main函数的定义
*************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
extern int GetNum (void);          /*  函数原型   */
extern void GuessNum(void);       /*  函数原型   */
int magic;                 /*  外部变量magic的定义, 等价于int magic=0   */

int main(void)
{

	char command;

    printf("This is a guessing game\n\n");
	srand(time(NULL));         /*  用系统时间初始化随机数生成器   */
    do
    {
		magic = GetNum( );     /*  调用GetNum产生随机数供猜测    */
	    GuessNum( );       /*    调用GuessNum猜出这个数    */
	    printf("Play again? (Y/N) ");
	    scanf("%1s", &command);     /*   询问是否继续   */
	} while (command == 'y' || command == 'Y');
     return 0;

}


