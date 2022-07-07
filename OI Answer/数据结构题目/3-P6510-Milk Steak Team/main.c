#include <stdio.h>
#include <stdlib.h>
// #define min(x, y) ((x) > (y) ? (y) : (x))
#define max(x, y) ((x) < (y) ? (y) : (x))
int height[100010], left[100010], right[100010];
//height array is used to store data
//The left array is used to maintain the minimum value, and ltop is the identifier of the top of the stack
//The right array is used to maintain the maximum value, and rtop is the identifier of the top of the stack
int main(void) {
	int n, result = -1, l, r, mid, ltop = 0, rtop = 0;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &height[i]);
		while (rtop && height[right[rtop]] < height[i])
			rtop--; //If the current element is larger than the corresponding element on the top of the stack and the stack is not empty, always pop out of the stack
		while (ltop && height[left[ltop]] >= height[i])
			ltop--; //If the current element is not larger than the corresponding element on the top of the stack and the stack is not empty, always pop out of the stack
		l = 1, r = ltop;
		while (l <= r) {
			int mid = (l + r) >> 1;
			if (left[mid] > right[rtop]) r = mid - 1;
			else l = mid + 1;
		}
		if (l != ltop + 1) result = max(result, i + 1 - left[l]);
		left[++ltop] = right[++rtop] = i;
	}
	if (result < 0)printf("0\n");
	else printf("%d\n", result);
	return 0;
}