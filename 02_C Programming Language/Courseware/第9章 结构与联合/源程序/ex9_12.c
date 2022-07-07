#include "stdio.h"
#define CHAR_BIT 8
struct w16_bytes{
	    unsigned short byte0:8,byte1:8; /* byte0为低字节,byte1为高字节 */
} ;
struct w16_bits{
	    unsigned short b0:1,b1:1,b2:1,b3:1,b4:1,b5:1,b6:1, 
		b7:1,b8:1,b9:1,b10:1,b11:1,b12:1,b13:1,b14:1,b15:1;
} ;
union w16{ /* 短整型变量、结构成员byte、结构成员bit共享共同的存储 */
	    short	i; 
	    struct w16_bytes		byte;	
	    struct w16_bits		bit;
} ;
int main(void)
{		union w16	w={0};/* i为0；byte0和byte1也为0；b0至b15皆为0 */
	    void bit_print(short);
	    w.bit.b9=1; /* 相当于byte0为2 */
	    w.bit.b10=1; /* 相当于byte0为6 */
	    w.byte.byte0='b';
	    printf("w.i=0x%x\n",w.i); /* 按整型解释、输出共享存储的内容 */
	    bit_print(w.i); /* 从高到低，逐位输出共享存储的各bit值 */
		return 0;
}
void bit_print(short num)
{		int i,shift=sizeof(short)*CHAR_BIT;
	    int mask=1<<(shift-1); /* 掩码mask的最高位为1，其余15位为0 */
	    for(i=1;i<=shift;i++){ 
		    putchar(((num & mask) == 0)? '0': '1'); /* num最高位为1，输出1 */
		    num<<=1; /* num左移1位；等价于：num = num<<1 */
		    if(i%CHAR_BIT==0 && i<shift) /* 每输出8位后，输出空格 */
			    putchar(' ');
	    }
	    putchar('\n');
}
