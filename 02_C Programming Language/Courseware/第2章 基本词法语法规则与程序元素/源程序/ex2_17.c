/************************************************************************************
简要描述：	读入一个字符，计算其奇偶校验位，并将其最高位设置成奇偶校验位。
*************************************************************************************/
#include<stdio.h>
int main()
{
	unsigned char data,backup,t;
	int parity=0;    /* 奇偶校验位,0-偶校验，1-奇校验  */

	data=getchar();   /* 被校验的数据  */
    backup=data;
    while (data)
    {
		t=data&1;   /* 取该数的最低位  */
		parity^=t;      /* 进行异或操作  */
		data>>=1;     /* 为取下一位做准备  */
	}
	data=backup|(parity<<7);    /* 生产校验码  */
	printf("The data is %#x\n",backup);
	printf("Parity-Check Code is %#x\n",data);    /* 输出校验码  */
	return 0;
}
