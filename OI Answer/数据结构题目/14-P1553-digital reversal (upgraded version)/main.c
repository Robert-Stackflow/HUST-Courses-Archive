#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void reverse(char *str, int l, int r) {
	for (int i = l; i <= (l + r) / 2; i++) {
		int temp = str[i];
		str[i] = str[l + r - i];
		str[l + r - i ] = temp;
	}
}
int main(void) {
	char str[25];
	int num = 0, mid = 0, imo = 1, flag = 0;
	scanf("%s", str);
	for (int i = 0; i < strlen(str); i++) {
		if (str[i] == '.' || str[i] == '/') {
			flag = 1;
			for (int j = i + 1; j < strlen(str); j++) {
				if (str[j] != '0') {
					imo = 0;
					break;
				}
			}
			reverse(str, 0, i - 1);
			reverse(str, i + 1, strlen(str) - 1);
		}
		if (str[i] == '%') {
			flag = 1;
			reverse(str, 0, i - 1);
		}
	}
	if (!flag)reverse(str, 0, strlen(str) - 1);
	flag = 0;
	for (int i = 0; i < strlen(str); i++) {
		if ((strlen(str) == 1 && str[0] == '0') || (strlen(str) == 2 && str[0] == '0' && str[1] == '%')) {
			printf("%s", str);
			return 0;
		}
		if (str[strlen(str) - 1] == '0' && !imo) {
			for (int j = strlen(str) - 1; str[j] == '0'; j--)
				str[j] = '\0';
		}//去除后导零
		if (str[0] == '0' && !flag && str[1] != '.' && str[1] != '/' ) {
			for (int j = 0; str[j] == '0'; j++)
				i++;
			flag = 1;
		}//去除前导零1
		if (str[i] == '/') {

			flag = 0;
			if (str[i + 1] == '0' && !flag) {
				printf("/");
				for (int j = i + 1; str[j] == '0'; j++)
					i++;
				i++;
			}
			flag = 1;
		}//去除前导零2
		printf("%c", str[i]);
	}
	return 0;
}