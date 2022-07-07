#include <stdio.h>
#include <stdlib.h>
#include <string.h>
const unsigned long long MOD = 212370440130137957ll;
const int MUL = 131;
const int p = 233317;

void quick_sort(unsigned long long *arr, int low, int high) {
	if (low < high) {
		int i = low;
		int j = high;
		unsigned long long k = arr[low];
		while (i < j) {
			while (i < j && arr[j] >= k) {  // 从右向左找第一个小于k的数
				j--;
			}
			if (i < j) {
				arr[i++] = arr[j];
			}
			while (i < j && arr[i] < k) {   // 从左向右找第一个大于等于k的数
				i++;
			}
			if (i < j) {
				arr[j--] = arr[i];
			}
		}
		arr[i] = k;
		// 递归调用
		quick_sort(arr, low, i - 1);     // 排序k左边
		quick_sort(arr, i + 1, high);    // 排序k右边
	}
}

unsigned long long Hash(char *str) {
	unsigned long long res = 0;
	for (int i = 0; i < strlen(str); i++) {
		res = (res * MUL + (unsigned long long)str[i]) % MOD + p;
	}
	return res;
}

int main(void) {
	int n, ans = 1;
	unsigned long long a[10050];
	char str[10050];
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%s", str);
		a[i] = Hash(str);
//		printf("=============%ull\n", a[i]);
	}
	quick_sort(a, 1, n);
//	for (int i = 1; i <= n; i++)
//		printf("`````````````%ull\n", a[i]);
	for (int i = 1; i < n; i++)
		if (a[i] != a[i + 1])
			ans++;
	printf("%d", ans);
	return 0;
}