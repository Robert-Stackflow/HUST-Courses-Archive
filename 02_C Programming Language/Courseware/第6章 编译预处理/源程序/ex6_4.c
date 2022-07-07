/******************************************************************
简要描述：采用条件编译，计算圆或正方形的面积。
*******************************************************************/
#include <stdio.h>
#define  R
int  main(void)
{
	float  r,area;
	printf("input a number:");
	scanf("%f",&r);
    #ifdef  R
        /*  如定义了标识符R，则计算圆的面积  */
        area=3.14159*r*r;
		printf("area of round is: %f\n",area);
    #else
         /* 如未定义标识符R，则计算正方形的面积  */
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
