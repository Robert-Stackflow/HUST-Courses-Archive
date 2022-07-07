#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <mmintrin.h>

#define LEN 100000 // 数组大小

int main() {
	clock_t stTime, edTime;
	int   i,j;
	unsigned short  a[LEN];
	unsigned short  b[LEN];
	unsigned short  c[LEN];
	__m64  *pa;
	__m64  *pb;
	__m64  *pc;
	int LEN4;

	srand(time(NULL));
	for (i = 0; i < LEN; i++) {
		a[i] = rand() ;
		b[i] = rand();
	}
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

	/*  Method 1 : 传统C 语句*/
/*	for (j = 0; j < 1000; j++) {
		for (i = 0; i < LEN; i++) {
			c[i] = a[i] + b[i];
		}
	}
*/	

	/*  Method 2 : MMX 指令 */
	/*
	__asm{
		    mov  ECX,1000
		l1: 
			lea  edi, a
			lea  esi, b
			lea  ebx, c
			mov  edx , LEN/4
		l2:
			  movq mm0, qword ptr [edi]
			  movq mm1, qword ptr [esi]
			  paddw mm0,mm1
			  movq  qword ptr[ebx],mm0
			  add  edi,8
			  add  esi,8
			  add  ebx,8
			  dec  edx
			  jnz  l2
			  dec  ecx
			  jnz  l1
			  emms
	}
	*/
	/*  Method 3 : 传统 CPU 指令 */
	/*
	__asm{
		mov  ECX, 1000
		l1:
		    lea  edi, a
			lea  esi, b
			lea  ebx, c
			mov  edx, LEN 
		l2 :
		   mov  AX, word ptr[edi]
		   add  AX, word ptr[esi]
		   mov  word ptr[ebx], AX 
		   add  edi, 2
		   add  esi, 2
		   add  ebx, 2
		   dec  edx
		   jnz  l2
		   dec  ecx
		   jnz  l1
	}
	*/
	edTime = clock();
	unsigned int spendtime = edTime - stTime;

	printf("time used: %d \n", spendtime);
	for (i = 0; i < 10; i++)
		printf("%d + %d = %d \n", a[i], b[i], c[i]);
	for (i = LEN-11; i < LEN; i++)
		printf("%d + %d = %d \n", a[i], b[i], c[i]);
	_getch();
	return 0;
}