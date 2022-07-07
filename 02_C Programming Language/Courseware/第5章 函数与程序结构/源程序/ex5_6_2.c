/************************************************************************************
 ��Ҫ����������������ر�汾����magic����Ϊ�ⲿ����,��������������ļ��С�
           ���ǵ�2�ļ�ex5_6_2.c: ����GetNum ��GuessNum�����Ķ���
*************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#define MAX_NUMBER 1000
extern int magic;  /*  �ⲿ����magic������   */
/****************************************************************
�������ƣ�GetNum
�������ܣ�����һ��1��MAX_NUMBER֮��������,����Ϸ�߲²⡣
������������
��������ֵ�����ز����������
*****************************************************************/
int GetNum(void)     /*  �ȼ��� GetNum( )    */
{
	printf("A magic number between 1 and %d has been chosen.\n",MAX_NUMBER);
	return (rand() % MAX_NUMBER + 1);
}

/****************************************************************
�������ƣ�GuessNum
�������ܣ���Ϸ�߸�����ʾ����������ֱ���¶�Ϊֹ����������Ĵ�����
������������
��������ֵ����
��ע�������������ⲿ����magic������Ϣ
****************************************************************/
void GuessNum ( )
{
	int guess,counter = 0;
	for (;;)
	{
        printf("guess it: ");
		scanf("%d", &guess);
        counter++;               /*   ͳ�ƲµĴ���   */
		if (guess == magic)
		{              /*   �¶�    */
			printf("You guessed the number by %d times!\n\n", counter);
            return;
		}
	    else if (guess < magic)            /*   ��С��   */
		    printf("Too low. Try again.\n");
        else                   /*   �´���   */
            printf("Too high. Try again.\n");
	}

}

