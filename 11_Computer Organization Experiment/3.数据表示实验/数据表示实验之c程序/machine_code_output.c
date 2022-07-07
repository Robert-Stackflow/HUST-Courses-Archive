//file: machine_code_output.c
#include <stdio.h>

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

main()
{
int a= -1;
int b=2147483648;           //2147483648=231    4294967296=232
int c= -b;
unsigned int d = -2147483648;
printf ("a = %u = %d = 0x%x  \n",a,a,a);
printf ("b = %u = %d = 0x%x  \n",b,b,b);
printf ("c = %u = %d = 0x%x  \n",c,c,c);
printf ("d = %u = %d = 0x%x  \n",d,d,d);

printf("\nd’s memory addr  = 0x%x",&d);  //输出变量d的虚存地址
printf("\nd’s machine code = 0x");
four_byte_out (&d);      //输出变量d的机器码

return;
}
