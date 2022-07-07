#include <stdio.h>
#include "ipp.h "

int ipp_add_float_array(Ipp32f *src1, Ipp32f *src2, Ipp32f *dst, Ipp32s len) {
	Ipp64u start, end;
	start = ippGetCpuClocks();
	ippsAdd_32f(src1, src2, dst, len);
	end = ippGetCpuClocks();
	return (int)(end - start);
}

int normal_add_float_array(float *src1, float *src2, float *dst, int len) {
	Ipp64u start, end;
	start = ippGetCpuClocks();
	for (int i = 0; i < len; i++) {
		dst[i] = src1[i] + src2[i];
	}
	end = ippGetCpuClocks();
	return (int)(end - start);
}

#define LEN 10000000
float src1[LEN], src2[LEN], dst[LEN];
int len = LEN;

int main() {
	for (int i = 0; i < len; i++) {
		src1[i] = src2[i] = i;
		dst[i] = 0;
	}
	int ipp_time = ipp_add_float_array(src1, src2, dst, len);
	for (int i = 0; i < len; i++) {
		src1[i] = src2[i] = i;
		dst[i] = 0;
	}
	int normal_time = normal_add_float_array(src1, src2, dst, len);

	printf("Clocks to add (ipp): %d \n", ipp_time);
	printf("Clocks to add (normal): %d \n", normal_time);
	printf("normal / ipp = %f", 1.0 * normal_time / ipp_time);

	return 0;
}
