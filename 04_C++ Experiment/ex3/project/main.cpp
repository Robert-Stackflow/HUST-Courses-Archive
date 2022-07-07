#include "Stack.h"
extern const char* TestSTACK(int& s);
int main()
{
    int s;
    const char* e = TestSTACK(s);
    std::cout << "Score:" << s << "\nResult:" << e << std::endl;
    system("pause");
    return 0;
}