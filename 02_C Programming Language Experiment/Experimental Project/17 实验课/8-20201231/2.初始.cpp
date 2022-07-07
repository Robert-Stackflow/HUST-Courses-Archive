#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//1.25 2.25 3.75 4.465 101.25 102.75 30.68 42.85 58.65 102.25
void D1toB(int integer,int radix,int result[], int &num);
void D2toB(float decimal,int radix,int result[], int &num);
void transform(float number);
void store(){
	FILE * fpout; 
	int i; 
	float f[10]; 
	if((fpout=fopen("d:\\float.dat","w"))==NULL) 
	{ 
		printf("Can't open this file!\n"); 
		exit(-1); 
	} 
	for(i=0;i<10;i++) 
	{
	scanf("%f",&f[i]);
	getchar();	
	} 
	fwrite(f,sizeof(float),10,fpout); 
	fclose(fpout);
}
void display()
{
	FILE * fpin;
	float f[10];  
	int i; 
	if((fpin=fopen("d:\\float.dat","r"))==NULL) 
	{ 
	printf("Can't open this file!\n"); 
	exit(-1); 
	} 
	for(i=0;i<10;i++) 	fread(&f[i],sizeof(float),1,fpin); 
	fclose(fpin);  	
	for(i=0;i<10;i++) 	transform(f[i]); 
}
int main()
{
	store();
	display();
    return 0;
}

//整数转r进制
//integer:整数 radix:进制 result:结果数组 num:生成r进制所占位数
void D1toB(int integer, int radix, int result[], int &num)
{
	int i, j, n;
	for (i = 0; integer > 0; i++)//除r取余
	{
		result[i] = integer % radix;
		integer = integer / radix;
	}
	num = i;//r进制位数
	for (j = 0; j < i / 2; j++)//颠倒顺序 
	{
		n = result[j];
		result[j] = result[i - 1 - j];
		result[i - 1 - j] = n;
	}
}

//小数转r进制
//decimal:小数 radix:进制 result:结果数组 num:生成r进制所占位数
void D2toB(float decimal, int radix, int result[], int &num)
{
	int i;
	for (i = 0; decimal > 0 && i < 50; i++)//乘r取整
	{
		result[i] = decimal * radix;
		decimal = decimal * radix;
		decimal = decimal - int(decimal);
	}
	num = i;
}

void transform(float number)
{
	int integer;//整数部分 
	float decimal;//小数部分 
	int s,p[8], m[50];//浮点数符号位，阶码数，尾数 
	while (true)
	{
		int i, j;
		for (i = 0; i < 8; i++)//清零
			p[i] = 0;
		for (i = 0; i < 50; i++)
			m[i] = 0;
		//确定符号位 
		if (number > 0)
			s = 0;
		else
		{
			s = 1;
			number=-number;
		}
		//将浮点数分成整数和小数 
		integer=(int)number;
		decimal=number-integer;
		//分别将整数和小数转化成二进制 
		int m_n1, m_n2;
		D1toB(integer,2,m,m_n1);
		D2toB(decimal,2,m + m_n1,m_n2);
		//规格化，计算阶数, 尾数
		int pn = 0;//阶数 
		if (integer > 0)//小数点左移
		{
			pn = m_n1 - 1;//阶数 
			for (i = 0; i < 23; i++)//去掉首位默认的1
			{
				m[i] = m[i + 1];
			}
		}
		else//小数点右移
		{
			for (i=0;m[i]==0;i++)
			{
			}pn = -i -1;
			for (j = 0; j < 23; j++)//去掉左边无效的0和第一个的1
				m[j] = m[j + 1 + i];
		}
		//计算阶码
		int p1[8],pn1;
		D1toB(pn + 127, 2, p1, pn1);//阶数转二进制 
		if (pn1 < 8)//不足8位左边补0 
		{
			for (j = 0; j < 8 - pn1; j++)
				p[j] = 0;
			for (int k = 0; k < pn1; k++)//得出完整p 
				p[j + k] = p1[k];
		}
		else
		{
			for (i= 0; i < 8; i++)//得出完整p 
				p[i] = p1[i];
		}
		//输出s
		printf("%d ", s); 
		//输出p
		for (i=0;i<8;i++)
			printf("%d", p[i]);
		printf(" "); //输出s
		//输出m
		for (i = 0; i < 23; i++)
		{
			printf("%d", m[i]);
		}
		printf("\n");
	}
}
