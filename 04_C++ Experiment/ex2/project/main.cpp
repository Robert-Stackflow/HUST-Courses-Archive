#include "Queue.h"
extern const char* TestQUEUE(int& s);
int main()
{
	int s;
	const char* e = TestQUEUE(s);
	std::cout << "Score:" << s << "\nReturn:" << e << std::endl;
	system("pause");
	return 0;
}