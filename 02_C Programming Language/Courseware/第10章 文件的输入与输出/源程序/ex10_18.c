#include "stdio.h"
#include "fcntl.h"
#include "stdlib.h"
#include "io.h"
void display(unsigned char * p); /* 显示汉字点阵字模函数 */
int getbit(unsigned char c,int n); 
int main(void)
{	int handle; /* 文件说明符 */
	unsigned int i,high_byte,low_byte,flag=0;
	int rec; /* 汉字位置指示 */
	long l;  /* 汉字点阵字模位置指示 */
	unsigned char f[30]="计算机程序设计语言"; /* 待显汉字串 */
	unsigned char by[32],*p = f; /* by为汉字点阵字模数组 */
	unsigned int m_code, a_code; /* m_code为机内码，a_code为区位码 */
	handle=open("c:\\HZK16",O_RDONLY|O_BINARY);/* 打开16 16点阵汉字库 */
//	handle=open("c:\\HZK16",_IOREAD|O_BINARY);/* 打开16 16点阵汉字库 */
	if(handle == -1){
		puts("Error on open cclib.dat\n");
		exit(1);
	}
	while(((i = *p++) != '\0') && i > 0xa1){
		if(flag == 0){ /* flag == 0，处理汉字机内码高字节 */
			high_byte=(i-0xa1)&0x07f;
			m_code = i<<8; 
			a_code = high_byte<<8; 
			flag = 1;
		}
		else{   /* flag != 0，处理汉字机内码低字节 */
			low_byte=(i-0xa1)&0x07f;
			m_code |= i; /* 得到汉字机内码 */
			a_code |= low_byte;  /* 得到汉字区位码 */
			flag = 0;
			rec = high_byte * 94 + low_byte; /* 汉字位置定位 */
			l = rec * 32L; /* 计算汉字点阵字模位置 */
			lseek(handle,l,SEEK_SET); /* 文件指针定位 */
			read(handle,by,32); /* 读指定汉字的点阵字模 */
			display(by); /* 以文本方式显示汉字点阵字模 */
			printf("inner code: 0x%x\tblock bits code: 0x%x\n",m_code,a_code);/* 显示机内码、区位码*/
			getchar(); /* 等待用户输入换行，以便处理下一个汉字 */
		}
	}
	return 0;
}
void display(unsigned char * p)
{	int i1,i2,i3,j=0;
	char c[16*16];
	i1=0;
	while(i1 < 256)
		c[i1++] = '.'; /* 初始化，所有bit为0；为0将显示'.' */
	for(i1=0;i1<16;i1++)
		for(i2=0;i2<2;i2++)
			for(i3=0;i3<8;i3++)
		/* 读点阵字模数组各字节，每字节从高位开始读；如果为1，则显示 */
				if(getbit(p[i1*2+i2],7-i3) == 1) 
					c[i1*16+i2*8+i3] = '1'; /* 该bit为1，显示'1' */
	for(i1 = 0; i1 < 16; i1++){ /* 以文本方式显示汉字点阵字模 */
		for(i2 = 0; i2 < 16; i2++)
			printf("%2c",c[i1*16+i2]); putchar('\n');
	}
}
int getbit(unsigned char c,int n)
{	return ((c>>n)&1); }/* 测试字节c的第n位是否为1 */
