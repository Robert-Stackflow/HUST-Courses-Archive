#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

 typedef  struct {
	int  x;      // 一个点的 x坐标
	int  y;      // 一个点的 y坐标
}POINT;

void  f1()
{
	char   s[10];
	strcpy(s,"1234567");
	printf("% x \n", *(long*)(s + 2));
	printf("% x \n", *(short*)(s + 2));
	printf("% d \n", *(char*)(s + 2));
	*(int*)(s + 1) = 16706;
	printf("% s \n", s);
}

int main(int argc, char* argv[])
{

	int points[100];
	f1();
	points[0] = 10;
	points[1] = 20;
	printf("%d %d\n", (*(POINT *)points).x, (*(POINT *)points).y);
	(*(POINT *)(points+2)).x = 110;
	(*(POINT *)&(points[2])).y = 120;
	return 0;
}