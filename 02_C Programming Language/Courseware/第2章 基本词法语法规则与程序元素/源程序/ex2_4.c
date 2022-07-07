/************************************************************************************
简要描述：转义序列的应用
*************************************************************************************/
#include<stdio.h>
int main(void)
{
      printf("\n\\n causes \na line feed to occur");
      printf("\n\\\"causes a double quote (\") to be printed");
      printf("\n\\a causes the bell,or beep, to sound\a");
      printf("\n\\t can be used to align some numbers to tab");
      printf("columns \n\t1\t2\t3\n\t4\t5\t6");
      return 0;
}
