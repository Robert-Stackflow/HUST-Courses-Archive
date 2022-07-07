#include <stdio.h>
int main(int argc, char* argv[])
{
    int x = 100;
    int y = 200;	
    int *p;
	char a[10] = "1234567";
	printf("%c %x\n", *(char*)a, *(char*)a);
	printf("%d %x\n", *(short*)a, *(short*)a);
	printf("%ld %x\n", *(int*)a, *(int*)a);

    printf("before update : x=%d  y=%d\n", x,y);
    p = &y;
    p = p + 1;
    *p = 400;
    p = p + 2;
	*p = 300;
	printf("after  update : x=%d  y=%d\n", x, y);
	return 0;
}