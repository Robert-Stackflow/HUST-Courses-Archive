/************************************************************************************
��Ҫ����������������ر�汾����magic����Ϊ�ⲿ����
 ����:�������һ��1��1000֮������������Ϸ�߲£�
      ����µò���ȷ,����᲻�ϵط�����ϢToo high��Too low,������ֱ����ȷΪֹ��
      ��������Ĵ�����
*************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_NUMBER 10
int GetNum (void);          /*  ����ԭ��   */
void GuessNum(void);       /*  ����ԭ��   */

int magic;      /*  �ⲿ����magic�Ķ���   */

int main(void)
{
	char command;
    extern int magic;    /*  �ⲿ����magic������   */

    printf("This is a guessing game\n\n");
	srand(time(NULL));         /*  ��ϵͳʱ���ʼ�������������   */
    do
    {
		magic = GetNum( );     /*   ����GetNum������������²�    */
	    GuessNum();       /*    ����GuessNum�³������    */
	    printf("Play again? (Y/N) ");
	    scanf("%1s", &command);     /*   ѯ���Ƿ����   */
	} while (command == 'y' || command == 'Y');
	return 0;
}

/****************************************************************
�������ƣ�GetNum
�������ܣ�����һ��1��MAX_NUMBER֮��������,����Ϸ�߲²⡣
������������
��������ֵ�����ز����������
*****************************************************************/
int GetNum(void)
{
	printf("A magic number between 1 and %d has been chosen.\n",MAX_NUMBER);
	return (rand() % MAX_NUMBER + 1);
}

/****************************************************************
�������ƣ�GuessNum
�������ܣ���Ϸ�߸�����ʾ����������ֱ���¶�Ϊֹ����������Ĵ�����
������������
��������ֵ����
****************************************************************/
void GuessNum ( )
{
	int guess,counter = 0;
	extern int magic;             /*  �ⲿ����magic������   */

	for (;;)
	{
        printf("guess it: ");
		scanf("%d", &guess);
        counter++;               /*   ͳ�ƲµĴ���   */
		if (guess == magic)    /*   �¶�    */
		{
			printf("You guessed the number by %d times!\n\n", counter);
            return;
		}
	    else if (guess < magic)            /*   ��С��   */
		    printf("Too low. Try again.\n");
        else                   /*   �´���   */
            printf("Too high. Try again.\n");
	}
}
