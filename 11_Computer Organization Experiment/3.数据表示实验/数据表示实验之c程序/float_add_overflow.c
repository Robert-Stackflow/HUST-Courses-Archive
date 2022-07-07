// file : float_add_overflow.c
# include "stdio.h"
union
{
char c[4];
float f;
int i;
}  t1,t2,t3,t4;

//输出字符的十六进制编码
void char_hex_out(char a)
{
 const char HEX[]="0123456789ABCDEF";
 int index=a&0x0F;
 printf("%c%c", HEX[(a&0xF0)>>4],HEX[a&0x0F]);
 }

 //输出4个字节数据的十六进制编码，可用于输出4字节变量的机器码
void four_byte_out (char *addr)
{
char_hex_out (*(addr +3));   //输出指针变量的值，指针本质上是内存地址，无符号数
char_hex_out (*(addr +2));   //假设采用小端存储
char_hex_out (*(addr +1));
char_hex_out (*(addr +0));
printf("\n");
}
void float_add_overflow()
{
  t1.i=0x7F000000;    t2.i=0x7F000000;
  t3.f=t1.f+t2.f;
  four_byte_out (&t1.f);          //该函数见1.1.3节程序中的定义
  four_byte_out (&t2.f);
  four_byte_out (&t3.f);
  printf("t1 = %.60f \n",t1.f);
  printf("t2 = %.60f \n",t2.f);
  printf("t1+t2 = %.60f \n",t3.f);
}

void float_sub_overflow()
{
  t1.i=0x00C00000;   t2.i=0x00800000;
  t3.f=t1.f-t2.f;
  four_byte_out (&t1.f);          //该函数见1.1.3节程序中的定义
  four_byte_out (&t2.f);
  four_byte_out (&t3.f);
  printf("t1 = %.61f \n",t1.f);
  printf("t2 = %.61f \n",t2.f);
  printf("t1-t2 = %.61f \n",t3.f);
}
main()
{
float_add_overflow();
float_sub_overflow();
}
