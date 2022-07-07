#include "stdio.h"
/* 下面的main为主函数名，前面的void表示无返回值，括号中的void表示无参 */
int main(void) 
{ /* main函数的函数体开始 */
	 int x,k,positive,negtive; /* 说明语句说明各个整型变量 */
k=1; /* 循环次数变量k赋初值1 */
	 positive=negtive =0;     /* 具有累加作用的变量清零 */
	 while(k<11)   /* 如果k<11，执行while循环体，否则转到循环体后一语句执行 */
	 {/* while循环体开始 */
		 scanf("%d",&x);  /* 接受从键盘输入的一个整数，并赋给变量x */
		 if(x!=0) /* 如果x?0，执行外层if块，否则转执行外层if块后一语句执行 */
		 {/*外层if块开始*/
			if(x>0)  /*如果x>0，执行内层if块，否则执行else块 */
			{/* 内层if块开始 */
				positive++;   /* 正整数个数加1 */
			}/* 内层if块结束 */
			else                  /* 如果x<0，转到此处执行 */
			{/* else块开始*/
				++negtive;    /* 负整数个数加1 */
			} /* else块结束 */
		 }/* 外层if块结束 */
		 k++; /* 循环次数变量k加1 */
	 } /* while循环体结束 */
	 printf("positive=%d \n",positive); /* 输出正数个数*/
	 printf("negtive=%d\n",negtive); /* 输出负数个数*/
	 return 0;
}                               /* main函数的函数体结束 */
