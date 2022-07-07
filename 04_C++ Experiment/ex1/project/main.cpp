#include "Queue.h"
extern const char* TestQueue(int& s);
int main()
{
	int s;
	const char* e = TestQueue(s);
	std::cout << "Score:" << s << "\nReturn:" << e << std::endl;
	system("pause");
	return 0;
}