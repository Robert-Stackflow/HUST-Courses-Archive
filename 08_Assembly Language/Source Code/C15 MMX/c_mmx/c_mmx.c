#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <mmintrin.h>

#define LEN 100000 // 数组大小

int main() {
	clock_t stTime, edTime;
	int   i, j;
	unsigned short  a[LEN];
	unsigned short  b[LEN];
	unsigned short  c[LEN];
	__m64  *pa;
	__m64  *pb;
	__m64  *pc;
	__m64  result;
	int LEN4;

	srand(time(NULL));
	for (i = 0; i < LEN; i++) {
		a[i] = rand();
		b[i] = rand();
	}
	a[0] = 1; a[1] = 2; a[2] = 3; a[3] = 4;
	b[0] = 2; b[1] = 3; b[2] = 4; b[3] = 5;
	result = _m_pmaddwd(*(__m64 *)a, *(__m64 *)b);
	stTime = clock();
	/*  Method 0 : C 对MMX的支持 语句*/
	for (j = 0; j < 1000; j++) {
		pa = (__m64 *)a;
		pb = (__m64 *)b;
		pc = (__m64 *)c;
		LEN4 = LEN / 4;
		for (i = 0; i < LEN4; i++) {
			*pc = _m_paddw(*pa, *pb);
			pa += 1;
			pb += 1;
			pc += 1;
		}
	}
	_m_empty();
	edTime = clock();
	unsigned int spendtime = edTime - stTime;

	printf("time used: %d \n", spendtime);
	for (i = 0; i < 10; i++)
		printf("%d + %d = %d \n", a[i], b[i], c[i]);
	for (i = LEN - 11; i < LEN; i++)
		printf("%d + %d = %d \n", a[i], b[i], c[i]);
	_getch();
	return 0;
}