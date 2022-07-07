#include <stdio.h>
char c;
int flag[62505] = {0}, w = 0, l = 0, sign[2] = {11, 21};
int main(void) {
	for (int i = 1; (c = getchar()) != 'E'; i++) {
		if (c == '\n' || c == '\r')i--;
		else if (c == 'W')flag[i] = 1;
		else flag[i] = -1;
	}
//	for (int i = 1; i < 30; i++) printf("%d", flag[i]);
//	printf("\n");
	for (int j = 0; j < 2; j++) {
		for (int i = 1;; i++) {
			if (flag[i] == 1) w++;
			else if (flag[i] == -1) l++;
			else {
				printf("%d:%d\n", w, l);
				break;
			}
//			printf("mid==========================%d:%d\n", w, l);
			if (w - l >= 2 || l - w >= 2) {
				if (w >= sign[j] || l >= sign[j]) {
					printf("%d:%d\n", w, l);
					w = l = 0;
				}
			}
		}
		w = l = 0;
		printf("\n");
	}
	return 0;
}