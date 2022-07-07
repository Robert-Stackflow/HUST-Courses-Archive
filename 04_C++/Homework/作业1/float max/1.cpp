#include <stdarg.h>
#include <iostream>
using namespace std;

float max(int c, ...)
{
	float maxn = -1;
	va_list ap;
	va_start(ap, c);
	maxn = va_arg(ap, double);
	for (int i = 1; i < c; i++)
	{
		float temp = va_arg(ap, double);
		if (maxn < temp)
			maxn = temp;
	}
	return maxn;
}

int main(void)
{
	cout << max(3, 1.1, 2.2, 3.3);
	return 0;
}