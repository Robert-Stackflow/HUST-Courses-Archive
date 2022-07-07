#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
	char ch;
	int b[1005], vb = 0, mid;
	while ((ch = getchar()) != '@') {
		if (ch <= '9' && ch >= '0') {
			int num = ch - '0';
			while ((ch = getchar()) != '.')
				num = num * 10 + ch - '0';
			b[vb++] = num;
		} else {
			switch (ch) {
				case '-':
					mid = b[vb - 2] - b[vb - 1];
					b[vb - 2] = mid;
					vb--;
					break;
				case '+':
					mid = b[vb - 2] + b[vb - 1];
					b[vb - 2] = mid;
					vb--;
					break;
				case '*':
					mid = b[vb - 2] * b[vb - 1];
					b[vb - 2] = mid;
					vb--;
					break;
				case '/':
					mid = b[vb - 2] / b[vb - 1];
					b[vb - 2] = mid;
					vb--;
					break;
			}
		}
	}
	printf("%d", b[0]);
	return 0;
}
