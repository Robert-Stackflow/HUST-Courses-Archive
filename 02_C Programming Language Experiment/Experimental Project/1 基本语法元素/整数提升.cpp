#include <stdio.h>
#include <stdlib.h>
 
int main()
{
	unsigned char a = 200;
	unsigned char b = 100;
	unsigned char c = 0;
	c = a + b;
	printf("%d %d \n",a+b,c);
	system("pause");
	return 0;
}                                  //�����300 44
 
//int  main(void)
//{
//	char a=97;
//	char b=98;
//	char c=a+b;
//	//ASCII�빲��127���ַ�
//	printf("a:%c\nb:%c\n",a,b);
//	//������������97��98���Բ�����01100001��01100010��
//	//��ӵõ�11000011������ԭ����10111101,����ʮ��������-61 
//	printf("%d",c);
//	return 0;
//};//�˴��ֺſɼӿɲ��� 

//int main()
//{
//	char c;
//	unsigned char uc;
//	unsigned short us;
//	c = 128;
//	uc = 128;
//	us = c + uc;
//	printf("0x%x\n",us);
//	us = (unsigned char)c + uc;
//	printf("0x%x\n",us);
//	us = c + (char)uc;
//	printf("0x%x\n",us);
// 
//	system("pause");
//	return 0;
//}                                  //�����0x0 0x100 0xff00
