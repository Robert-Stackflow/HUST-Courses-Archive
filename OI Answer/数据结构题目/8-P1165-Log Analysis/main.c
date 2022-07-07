#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max(x,y) ((x)<(y)?(y):(x))

int main(void) {
	int n, op, num, stack[200005], top = 0, mid[200005];
	mid[0] = 0;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &op);
		switch (op) {
			case 0:
				scanf("%d", &num);
				stack[top++] = num;
				mid[top] = max(mid[top - 1], num);
				break;
			case 1:
				if (!top)
					break;
				top--;
				break;
			case 2:
				printf("%d\n", mid[top]);
		}
	}
	return 0;
}