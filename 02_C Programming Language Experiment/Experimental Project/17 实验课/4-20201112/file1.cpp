/*Դ�ļ�file1.c������*/
#include"file.h"
#include"file2.cpp" 
int x,y; 
char ch;
int main (void)
	{
	x=10;
	y=20;
	ch=getchar();
	printf("in file1 x=%d,y=%d,ch is %c\n",x,y,ch);
	func1(x,y,ch);
	return 0;
}

