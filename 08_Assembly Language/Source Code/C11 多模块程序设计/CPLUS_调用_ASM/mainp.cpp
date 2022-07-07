#include <stdio.h>
#include <conio.h>
extern "C" void __cdecl SORT_PESUDO(int *, int);
//extern "C" void __stdcall SORT_PESUDO(int *, int);
extern "C" int y;
int main()
{
	int  a[5];
	int  i;
	printf("y= %d\n", y);
	for (i = 0; i < 5; i++)
		scanf_s("%d", &a[i]);
	printf("\n result after sort \n");
	SORT_PESUDO(a, 5);
	for (i = 0; i < 5; i++)
		printf("%d ", a[i]);
	_getch();
	return 0;
}