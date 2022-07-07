#include <stdio.h>
#define max(x,y) ((x)>(y)?(x):(y))

int rexp(int ans) {
	char ch;
	while ((ch = getchar()) != EOF) {
		if (ch == 'a')
			ans++;//如果是a则ans++
		else if (ch == '(')//如果是左括号则递归计算括号内内容
			ans += rexp(0);
		else if (ch == '|') { //如果是分隔符则比较分隔符左侧结果和右侧结果
			int num = rexp(0);
			return max(ans, num);
		} else if (ch == ')') //如果是右括号返回括号内结果
			return ans;
	}
	return ans;
}

int main() {
	printf("%d", rexp(0));
	return 0;
}