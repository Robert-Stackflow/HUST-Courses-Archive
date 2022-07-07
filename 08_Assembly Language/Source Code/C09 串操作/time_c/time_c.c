#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>
#define M 1000
#define N 10
int a[M][N];
int b[M][N];
void assign_array_rows()
{
	int i, j;
	for (i = 0; i<M; i++)
	for (j = 0; j < N; j++)
		//  a[i][j] = 0;
		b[i][j] = a[i][j];
}
void assign_array_cols()
{
	int i, j;
	for (j = 0; j<N; j++)
	   for (i = 0; i<M; i++)
		  a[i][j] = 0;
}

void assign_array_memset()
{
//	memset(a,0,sizeof(int)*M*N);
	memset(a, 0x12345678, M*N);
}

void array_copy()
{
	//	memset(a,0,sizeof(int)*M*N);
	memcpy(b, a, sizeof(int)*M*N);
}

void array_compare()
{
	int  qq[M][N];
	memset(a,0,sizeof(int)*M*N);

	memset(qq, 0, sizeof(int)*M*N);

	memset(&(a[0][0]), 0, sizeof(int)*M*N);
//	int xx=memcmp(b, a, sizeof(int)*M*N);
	char  a[100] = "this is a test";
	char  b[100] = "this is a test";
	char  *p;
	int x = strcmp(a,b);
	p=memchr(a, 'a', 100);
}
int main()
{
	clock_t start, finish;
	double  duration;
	start = clock();
	assign_array_rows();
	finish = clock();
	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("行优先用时： %f seconds\n", duration);

	start = clock();
	assign_array_cols();
	finish = clock();
	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("列优先用时： %f seconds\n", duration);

	a[0][0] = 20;
	a[0][1] = 40;
	a[1][0] = 60;
	a[1][1] = 80;
	start = clock();
//	assign_array_memset();
//	array_copy();
	array_compare();

	finish = clock();
	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("memset 时： %f seconds\n", duration);

	system("pause");
	return 0;
}
