#include <stdio.h>
#define max(x,y) ((x)>(y)?(x):(y))

int rexp(int ans) {
	char ch;
	while ((ch = getchar()) != EOF) {
		if (ch == 'a')
			ans++;//�����a��ans++
		else if (ch == '(')//�������������ݹ��������������
			ans += rexp(0);
		else if (ch == '|') { //����Ƿָ�����ȽϷָ�����������Ҳ���
			int num = rexp(0);
			return max(ans, num);
		} else if (ch == ')') //����������ŷ��������ڽ��
			return ans;
	}
	return ans;
}

int main() {
	printf("%d", rexp(0));
	return 0;
}