/******************************************************************
��Ҫ�����������������룬����Բ�������ε������
*******************************************************************/
#include <stdio.h>
#define  R
int  main(void)
{
	float  r,area;
	printf("input a number:");
	scanf("%f",&r);
    #ifdef  R
        /*  �綨���˱�ʶ��R�������Բ�����  */
        area=3.14159*r*r;
		printf("area of round is: %f\n",area);
    #else
         /* ��δ�����ʶ��R������������ε����  */
		area=r*r;
		printf("area of square is: %f\n",area);
    #endif
    return 0;

}

#define  US          0
#define  ENGLAND   1
#define  FRANCE     2
# define  ACTIVE_COUNTRY   US
#if  ACTIVE_COUNTRY == US
    char currency[ ]= "dollar";
#elif  ACTIVE_COUNTRY==ENGLAND
    char currency[ ]= "pound";
#else
    char currency[ ]= "franc";
#endif
