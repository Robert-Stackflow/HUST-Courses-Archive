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
}                                  //结果：300 44
 
//int  main(void)
//{
//	char a=97;
//	char b=98;
//	char c=a+b;
//	//ASCII码共有127个字符
//	printf("a:%c\nb:%c\n",a,b);
//	//溢出结果分析：97与98各自补码是01100001和01100010，
//	//相加得到11000011，而其原码是10111101,而其十进制正是-61 
//	printf("%d",c);
//	return 0;
//};//此处分号可加可不加 

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
//}                                  //结果：0x0 0x100 0xff00
