#include "stdio.h"
int main(void)
{	long x=0x1234ABCD,k; 
	char *p=(char *)&x;       /*����ǿ�ƣ�x����Ϊ4�ֽ��ַ����鱻p��ָ*/
	char up_half,low_half;    /*up_half���4λ��low_half���4λ*/
	for(k=0;k<4;k++)
	{	low_half=(*p)&0x0f;   /*ȡ��4λ*/
		if(low_half<10)
		  low_half|='0';      /*��4λ������ת����ASCII��'0'-'9'*/
		else
			low_half=(low_half-10)+'A';/*��4λ������ת����ASCII��'A'-'F'*/
		up_half=(*p>>4)&0x0f;    /*ȡ��4λ*/
		if(up_half<10)
		  up_half|='0';          /*��4λ������ת����ASCII��'0'-'9'*/
		else
		  up_half=(up_half-10)+'A';/*��4λ������ת����ASCII��'A'-'F'*/
		p++;  /*ָ��������x��һ���ֽ�*/
		printf("%c    %c\n",up_half,low_half);
	  }
	  return 0;
}
