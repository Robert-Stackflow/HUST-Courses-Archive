#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define mod 10000

int main(void) {
	long long ans = 0, num = 0, mid = 0, flag = 1;
	char ch1, ch2;
	ch1 = ch2 = '#';
	while (1) {
		scanf("%lld", &num);
		scanf("%c", &ch2);
		if (ch2 == '\n')
			flag = 0;
		if (ch1 == '#')
			mid = num;
		if (ch1 == '+')
			ans += mid, mid = num, ans %= mod;
		if (ch1 == '*')
			mid = mid * num, mid %= mod;
		if (!flag) {
			ans += mid;
			ans %= mod;
			break;
		}

		ch1 = ch2;
	}
	printf("%lld", ans);
	return 0;
}
