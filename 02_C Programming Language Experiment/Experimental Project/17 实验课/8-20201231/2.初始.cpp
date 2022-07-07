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

//����תr����
//integer:���� radix:���� result:������� num:����r������ռλ��
void D1toB(int integer, int radix, int result[], int &num)
{
	int i, j, n;
	for (i = 0; integer > 0; i++)//��rȡ��
	{
		result[i] = integer % radix;
		integer = integer / radix;
	}
	num = i;//r����λ��
	for (j = 0; j < i / 2; j++)//�ߵ�˳�� 
	{
		n = result[j];
		result[j] = result[i - 1 - j];
		result[i - 1 - j] = n;
	}
}

//С��תr����
//decimal:С�� radix:���� result:������� num:����r������ռλ��
void D2toB(float decimal, int radix, int result[], int &num)
{
	int i;
	for (i = 0; decimal > 0 && i < 50; i++)//��rȡ��
	{
		result[i] = decimal * radix;
		decimal = decimal * radix;
		decimal = decimal - int(decimal);
	}
	num = i;
}

void transform(float number)
{
	int integer;//�������� 
	float decimal;//С������ 
	int s,p[8], m[50];//����������λ����������β�� 
	while (true)
	{
		int i, j;
		for (i = 0; i < 8; i++)//����
			p[i] = 0;
		for (i = 0; i < 50; i++)
			m[i] = 0;
		//ȷ������λ 
		if (number > 0)
			s = 0;
		else
		{
			s = 1;
			number=-number;
		}
		//���������ֳ�������С�� 
		integer=(int)number;
		decimal=number-integer;
		//�ֱ�������С��ת���ɶ����� 
		int m_n1, m_n2;
		D1toB(integer,2,m,m_n1);
		D2toB(decimal,2,m + m_n1,m_n2);
		//��񻯣��������, β��
		int pn = 0;//���� 
		if (integer > 0)//С��������
		{
			pn = m_n1 - 1;//���� 
			for (i = 0; i < 23; i++)//ȥ����λĬ�ϵ�1
			{
				m[i] = m[i + 1];
			}
		}
		else//С��������
		{
			for (i=0;m[i]==0;i++)
			{
			}pn = -i -1;
			for (j = 0; j < 23; j++)//ȥ�������Ч��0�͵�һ����1
				m[j] = m[j + 1 + i];
		}
		//�������
		int p1[8],pn1;
		D1toB(pn + 127, 2, p1, pn1);//����ת������ 
		if (pn1 < 8)//����8λ��߲�0 
		{
			for (j = 0; j < 8 - pn1; j++)
				p[j] = 0;
			for (int k = 0; k < pn1; k++)//�ó�����p 
				p[j + k] = p1[k];
		}
		else
		{
			for (i= 0; i < 8; i++)//�ó�����p 
				p[i] = p1[i];
		}
		//���s
		printf("%d ", s); 
		//���p
		for (i=0;i<8;i++)
			printf("%d", p[i]);
		printf(" "); //���s
		//���m
		for (i = 0; i < 23; i++)
		{
			printf("%d", m[i]);
		}
		printf("\n");
	}
}
