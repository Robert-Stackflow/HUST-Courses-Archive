#include "stdio.h"
#define CHAR_BIT 8
struct w16_bytes{
	    unsigned short byte0:8,byte1:8; /* byte0Ϊ���ֽ�,byte1Ϊ���ֽ� */
} ;
struct w16_bits{
	    unsigned short b0:1,b1:1,b2:1,b3:1,b4:1,b5:1,b6:1, 
		b7:1,b8:1,b9:1,b10:1,b11:1,b12:1,b13:1,b14:1,b15:1;
} ;
union w16{ /* �����ͱ������ṹ��Աbyte���ṹ��Աbit����ͬ�Ĵ洢 */
	    short	i; 
	    struct w16_bytes		byte;	
	    struct w16_bits		bit;
} ;
int main(void)
{		union w16	w={0};/* iΪ0��byte0��byte1ҲΪ0��b0��b15��Ϊ0 */
	    void bit_print(short);
	    w.bit.b9=1; /* �൱��byte0Ϊ2 */
	    w.bit.b10=1; /* �൱��byte0Ϊ6 */
	    w.byte.byte0='b';
	    printf("w.i=0x%x\n",w.i); /* �����ͽ��͡��������洢������ */
	    bit_print(w.i); /* �Ӹߵ��ͣ���λ�������洢�ĸ�bitֵ */
		return 0;
}
void bit_print(short num)
{		int i,shift=sizeof(short)*CHAR_BIT;
	    int mask=1<<(shift-1); /* ����mask�����λΪ1������15λΪ0 */
	    for(i=1;i<=shift;i++){ 
		    putchar(((num & mask) == 0)? '0': '1'); /* num���λΪ1�����1 */
		    num<<=1; /* num����1λ���ȼ��ڣ�num = num<<1 */
		    if(i%CHAR_BIT==0 && i<shift) /* ÿ���8λ������ո� */
			    putchar(' ');
	    }
	    putchar('\n');
}
