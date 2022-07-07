#include <stdio.h>
char str[500];
int stack[500], len, mid[500];

int turtle(int l, int r) {
	if (str[l] == 'R')
		return mid[l] * turtle(l + 2, mid[l + 1]) + turtle(mid[l + 1] + 1,
		        r);                                                                                                               //��Ĳ���
	else {
		int i, ans = 0;
		for (i = l; i < r && str[i] != 'R'; i++) {
			if (str[i] == 'F')//ǰ����
				ans += mid[i];
			else                //���˼�
				ans -= mid[i];
		}
		if (i < r)
			ans += turtle(i, r);
		return ans;
	}
}

int abs(int x) {
	return x < 0 ? -x : x;
}

int main() {
	char c = getchar();
	int top = -1, i, ans, num;
	while (c != EOF) {//�����������s����
		if (c == '[') {
			stack[++top] = len;
			str[len++] = '[';
		} else if (c == ']') {
			mid[mid[len] = stack[top]] = len;
			stack[top--] = 0;
			str[len++] = ']';
		} else if (c == 'B' || c == 'F' || c == 'R') {
			str[len] = c;
			while (c < '0' || c > '9')
				c = getchar();
			num = 0;
			while (c >= '0' && c <= '9') { //��������(�����������˶����Ż�)
				num = num * 10 + c - '0';
				c = getchar();
			}
			mid[len++] = num;
			continue;
		}
		c = getchar();
	}
	printf("%d", abs(turtle(0, len)));
	return 0;
}