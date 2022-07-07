#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
	int n, top = 0;
	scanf("%d", &n);
	int stack[3000005], num[3000005], f[3000005];
	for (int i = 1; i <= n; i++)
		scanf("%d", &num[i]);
	for (int i = n; i >= 1; i--) {
		while (top > 0 && num[stack[top]] <= num[i])
			top--; //如果栈不为空而且栈顶小于等于当前元素则出栈
		f[i] = !top ? 0 : stack[top];//如果栈为空则没有比这个数更大的为0，否则为栈顶元素
		stack[++top] = i;//下标入栈
	}
	for (int i = 1; i <= n; i++)
		printf("%d ", f[i]);
	return 0;
}