/************************************************************************************
 ��Ҫ����������������ر�汾����magic����Ϊ�ⲿ����,��������������ļ��С�
           ���ǵ�1�ļ�ex5_6_1.c: �����ⲿ����magic��main�����Ķ���
*************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
extern int GetNum (void);          /*  ����ԭ��   */
extern void GuessNum(void);       /*  ����ԭ��   */
int magic;                 /*  �ⲿ����magic�Ķ���, �ȼ���int magic=0   */

int main(void)
{

	char command;

    printf("This is a guessing game\n\n");
	srand(time(NULL));         /*  ��ϵͳʱ���ʼ�������������   */
    do
    {
		magic = GetNum( );     /*  ����GetNum������������²�    */
	    GuessNum( );       /*    ����GuessNum�³������    */
	    printf("Play again? (Y/N) ");
	    scanf("%1s", &command);     /*   ѯ���Ƿ����   */
	} while (command == 'y' || command == 'Y');
     return 0;

}


