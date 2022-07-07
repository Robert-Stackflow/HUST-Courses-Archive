#include <stdio.h>
#include <string.h>
#include "ipp.h "

int memcpy_copy(const int * src, int * dst, int len) {
	Ipp64u start, end;
	start = ippGetCpuClocks();
	memcpy(dst, src, sizeof(int) * len);
	end = ippGetCpuClocks();
	return (int)(end - start);
}

int normal_copy(const int * src, int * dst, int len) {
	Ipp64u start, end;
	start = ippGetCpuClocks();
	for (int i = 0; i < len; i++) {
		dst[i] = src[i];
	}
	end = ippGetCpuClocks();
	return (int)(end - start);
}

int ipp_copy(const Ipp32s * src, Ipp32s * dst, int len) {
	Ipp64u start, end;
	start = ippGetCpuClocks();
	ippsCopy_32s(src, dst, len);
	end = ippGetCpuClocks();
	return (int)(end - start);
}

#define LEN 10000000
int src[LEN], dst[LEN];
int len = LEN;

int main() {

	for (int i = 0; i < len; i++) {
		src[i] = i;
		dst[i] = 0;
	}
	int normal_time = normal_copy(src, dst, len);
	for (int i = 0; i < len; i++) {
		src[i] = i;
		dst[i] = 0;
	}
	int memcpy_time = memcpy_copy(src, dst, len);
	for (int i = 0; i < len; i++) {
		src[i] = i;
		dst[i] = 0;
	}
	int ipp_time = ipp_copy(src, dst, len);

	printf("Clocks to copy (ipp): %d \n", ipp_time);
	printf("Clocks to copy (memcpy): %d \n", memcpy_time);
	printf("Clocks to copy (normal): %d \n", normal_time);
	printf("memcpy_time / ipp = %f\n", 1.0 * memcpy_time / ipp_time);
	printf("normal / ipp = %f", 1.0 * normal_time / ipp_time);
	
	return 0;

}