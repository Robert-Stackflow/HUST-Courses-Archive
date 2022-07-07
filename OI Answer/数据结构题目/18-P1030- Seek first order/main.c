#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char in[20], post[20], pre[20];
int top, inl, inr, postl, postr;

void trans(int l1, int r1, int l2, int r2) {
	int i = 0;
	pre[top++] = post[r2];
//	printf("%d %d %d %d %c %c\n", l1, r1, l2, r2, pre[top - 1], post[r2]);
	if (r1 == l1)
		return;
	for (i = l1; i <= r1; i++)
		if (in[i] == post[r2])
			break;
//	printf("============%d  %c\n", i, in[i]);
	if (i > l1)
		trans(l1, i - 1, l2, l2 + i - 1 - l1);
	if (i < r1)
		trans(i + 1, r1, r2 - r1 + i, r2 - 1);
}

int main(void) {
	scanf("%s%s", in, post);
	trans(0, strlen(in) - 1, 0, strlen(post) - 1);
	printf("%s", pre);
	return 0;
}