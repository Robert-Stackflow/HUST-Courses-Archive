#include <stdio.h>
#include <xmmintrin.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

// һ�� __m128 �����д洢 4 �� �������͵�ֵ
void mmx_add(const float * src1, const float & src2, float * dst, int len) {
	__m128 val = _mm_set_ps1(src2);
	int len4 = len / 4 + ((len % 4) != 0);
	for (int i = 0; i < len4; ++i) {
		*(__m128 *)(dst + i * 4) = _mm_mul_ps(*(__m128 *)(src1 + i * 4), val);
	}
}

void normal_mul(const float * src1, const float & src2, float * dst, int len) {
	for (int i = 0; i < len; ++i) {
		dst[i] = src1[i] * src2;
	}
}

#define LEN 1000001 // �����С

float __declspec(align(32)) src1[LEN];
float src2;
float __declspec(align(32)) dst[LEN];
int len = LEN;
int epochs = 1000; // �˷������Ĵ���

int main() {

	srand(time(NULL));

	clock_t stTime, edTime;

	for (int i = 0; i < len; i++) {
		src1[i] = rand() % 100 + (rand() % 10000) * 10e-4;
	}
	src2 = rand() % 1000 + (rand() % 10000) * 10e-4;
	
	// ʹ�� sse �� _mm_mul_ps �������г˷�����
	stTime = clock();
	for (int i = 0; i < epochs; i++) {
		sse_mul(src1, src2, dst, len);
	}
	edTime = clock();
	int sse_time = edTime - stTime;

	// ����ĳ˷�
	stTime = clock();
	for (int i = 0; i < epochs; i++) {
		normal_mul(src1, src2, dst, len);
	}
	edTime = clock();
	int normal_time = edTime - stTime;
	
	printf("sse: %fs\n", 1.0 * sse_time / CLOCKS_PER_SEC);
	printf("normal: %fs\n", 1.0 * normal_time / CLOCKS_PER_SEC);
	printf("normal / sse = %f", 1.0 * normal_time / sse_time);

	return 0;
}