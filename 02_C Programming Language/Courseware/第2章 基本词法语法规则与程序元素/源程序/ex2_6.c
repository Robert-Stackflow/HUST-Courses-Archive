/************************************************************************************
简要描述：打印华氏和摄氏温度对照表
*************************************************************************************/
#include<stdio.h>
#define LOWER 0       /*  表的下限  */
#define UPPER 300     /*  表的上限  */
#define STEP 20       /*  步长      */

int main(void)
{
    int fahr;
    for(fahr=LOWER;fahr<=UPPER;fahr=fahr+STEP)
          printf("%3d:%10.2f\n" , fahr, (5.0/9)*(fahr-32) );
    return 0;
}
