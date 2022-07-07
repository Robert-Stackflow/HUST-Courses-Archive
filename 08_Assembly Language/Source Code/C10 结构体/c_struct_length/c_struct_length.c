#include <stdio.h>
#include <stddef.h>
#pragma pack(1)
typedef  struct t{
	char f1;
	int  f2;
}temps;

int i = sizeof(temps);        // i=8
int j = offsetof(temps, f1);  // j=0
int k = offsetof(temps, f2);  // k=4
void main()
{

  printf("%d %d %d\n", i, j, k);
}
