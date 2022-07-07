#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxn 500005
long long ans;

void mergesort(int *a, int l, int *b, int r) {
	if (l == r)
		return;
	int mid = (l + r) / 2, i = l, j = mid + 1, k = l;
	mergesort(a, l, b, mid), mergesort(a, mid + 1, b, r);
	while (i <= mid && j <= r) //如果左区间和右区间均未读完
		if (a[i] <= a[j]) //如果左区间的元素比右区间元素小那么将该元素放入结果数组b
			b[k++] = a[i++];
		else//如果左区间的元素比右区间元素大那么可构成逆序对，而且该元素后的元素均可构成逆序对，写入答案并将右区间元素放入结果数组b
			b[k++] = a[j++], ans += mid - i + 1;
	while (i <= mid) //放入左区间剩余元素
		b[k++] = a[i++];
	while (j <= r) //放入右区间剩余元素
		b[k++] = a[j++];
	for (int m = l; m <= r; m++) //将结果数组写入原数组中
		a[m] = b[m];
}

int main(void) {
	int n, num[maxn], temp[maxn];
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &num[i]);
	mergesort(num, 1, temp, n);
	printf("%lld\n", ans);
	return 0;
}
