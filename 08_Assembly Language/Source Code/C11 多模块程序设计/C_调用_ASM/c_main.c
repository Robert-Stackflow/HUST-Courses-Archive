#include <stdio.h>
#include <conio.h>

int  x[5];
extern int y;

void SORT_PESUDO(int*, int);  // 在汇编程序中排序
void modify_in_asm();         // 在汇编程序在修改全局变量 x

int main()
{
	int  a[5];
	int  i;
	a[10000] = 10;
	//SORT2();
	printf("y is defined in asm file, y= %d \n", y);
	printf("please intput 5 numbers : \n");
	for (i = 0; i < 5; i++)
		scanf_s("%d", &a[i]);

	SORT_PESUDO(a, 5);
	printf("\n result after sort \n");
	for (i = 0; i < 5; i++)
		printf("%d ", a[i]);
	
	x[0] = 12; 
	x[1] = 23;
	printf("\n before modify: x[0]= %d   x[1]=%d\n", x[0], x[1]);
	modify_in_asm();
	printf("\n after modify: x[0]= %d   x[1]=%d\n", x[0], x[1]);

	_getch();
	return 0;
}