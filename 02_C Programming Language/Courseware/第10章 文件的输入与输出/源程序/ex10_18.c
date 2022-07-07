#include "stdio.h"
#include "fcntl.h"
#include "stdlib.h"
#include "io.h"
void display(unsigned char * p); /* ��ʾ���ֵ�����ģ���� */
int getbit(unsigned char c,int n); 
int main(void)
{	int handle; /* �ļ�˵���� */
	unsigned int i,high_byte,low_byte,flag=0;
	int rec; /* ����λ��ָʾ */
	long l;  /* ���ֵ�����ģλ��ָʾ */
	unsigned char f[30]="����������������"; /* ���Ժ��ִ� */
	unsigned char by[32],*p = f; /* byΪ���ֵ�����ģ���� */
	unsigned int m_code, a_code; /* m_codeΪ�����룬a_codeΪ��λ�� */
	handle=open("c:\\HZK16",O_RDONLY|O_BINARY);/* ��16 16�����ֿ� */
//	handle=open("c:\\HZK16",_IOREAD|O_BINARY);/* ��16 16�����ֿ� */
	if(handle == -1){
		puts("Error on open cclib.dat\n");
		exit(1);
	}
	while(((i = *p++) != '\0') && i > 0xa1){
		if(flag == 0){ /* flag == 0�������ֻ�������ֽ� */
			high_byte=(i-0xa1)&0x07f;
			m_code = i<<8; 
			a_code = high_byte<<8; 
			flag = 1;
		}
		else{   /* flag != 0�������ֻ�������ֽ� */
			low_byte=(i-0xa1)&0x07f;
			m_code |= i; /* �õ����ֻ����� */
			a_code |= low_byte;  /* �õ�������λ�� */
			flag = 0;
			rec = high_byte * 94 + low_byte; /* ����λ�ö�λ */
			l = rec * 32L; /* ���㺺�ֵ�����ģλ�� */
			lseek(handle,l,SEEK_SET); /* �ļ�ָ�붨λ */
			read(handle,by,32); /* ��ָ�����ֵĵ�����ģ */
			display(by); /* ���ı���ʽ��ʾ���ֵ�����ģ */
			printf("inner code: 0x%x\tblock bits code: 0x%x\n",m_code,a_code);/* ��ʾ�����롢��λ��*/
			getchar(); /* �ȴ��û����뻻�У��Ա㴦����һ������ */
		}
	}
	return 0;
}
void display(unsigned char * p)
{	int i1,i2,i3,j=0;
	char c[16*16];
	i1=0;
	while(i1 < 256)
		c[i1++] = '.'; /* ��ʼ��������bitΪ0��Ϊ0����ʾ'.' */
	for(i1=0;i1<16;i1++)
		for(i2=0;i2<2;i2++)
			for(i3=0;i3<8;i3++)
		/* ��������ģ������ֽڣ�ÿ�ֽڴӸ�λ��ʼ�������Ϊ1������ʾ */
				if(getbit(p[i1*2+i2],7-i3) == 1) 
					c[i1*16+i2*8+i3] = '1'; /* ��bitΪ1����ʾ'1' */
	for(i1 = 0; i1 < 16; i1++){ /* ���ı���ʽ��ʾ���ֵ�����ģ */
		for(i2 = 0; i2 < 16; i2++)
			printf("%2c",c[i1*16+i2]); putchar('\n');
	}
}
int getbit(unsigned char c,int n)
{	return ((c>>n)&1); }/* �����ֽ�c�ĵ�nλ�Ƿ�Ϊ1 */
