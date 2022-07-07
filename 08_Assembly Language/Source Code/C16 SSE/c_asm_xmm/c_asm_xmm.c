#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <emmintrin.h>

#define LEN 100000 // �����С

int main() {
	clock_t stTime, edTime;
	int   i, j;
	 _declspec(align(16)) unsigned short  a[LEN];
	 _declspec(align(16)) unsigned short  b[LEN];
	 _declspec(align(16)) unsigned short  c[LEN];
	/*  ��������������
	unsigned short  a[LEN];
	unsigned short  b[LEN];
	unsigned short  c[LEN];
	*/
	__m128i  *pa;
	__m128i  *pb;
	__m128i  *pc;
	__m128  t;
	int LEN8;

	srand(time(NULL));
	for (i = 0; i < LEN; i++) {
		a[i] = rand();
		b[i] = rand();
	}
	stTime = clock();
	/*  Method 0 : C ��MMX��֧�� ���*/
	
	for (j = 0; j < 1000; j++) {
		pa = (__m128i *)a;
		pb = (__m128i *)b;
		pc = (__m128i *)c;
		LEN8 = LEN / 8;
		for (i = 0; i < LEN8; i++) {
		    t = _mm_add_ss(*(__m128 *)a,*(__m128 *)b);
			*pc = _mm_adds_epu16(*pa, *pb);
			pa += 1;
			pb += 1;
			pc += 1;
		}
	}
	

	/*  Method 1 : ��ͳC ���*/
	/*	for (j = 0; j < 1000; j++) {
	for (i = 0; i < LEN; i++) {
	c[i] = a[i] + b[i];
	}
	}
	*/

	/*  Method 2 : MMX ָ�� */
	
		__asm{
	mov  ECX,1000
	l1:
					lea  edi, a
						lea  esi, b
							lea  eax, c
	mov  edx , LEN/8
	l2:
			movdqu xmm0, xmmword ptr[esi]
				paddusw xmm0, xmmword ptr[edi]
				movdqu  xmmword ptr[eax], xmm0
				add  edi, 16
				add  esi, 16
				add  eax, 16
				dec  edx
				jnz  l2
				dec  ecx
				jnz  l1
	}
	
	/*  Method 3 : ��ͳ CPU ָ�� */
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
	for (i = LEN - 11; i < LEN; i++)
		printf("%d + %d = %d \n", a[i], b[i], c[i]);
	_getch();
	return 0;
}