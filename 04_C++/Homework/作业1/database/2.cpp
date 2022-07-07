#include <cmath>
#include <cstring>
#include <iostream>
using namespace std;
char *numConvert(int desBase, int srcBase, int num)
{
    char *s = (char *)malloc(sizeof(char));
    int dec = 0, len = 0;
    for (int i = 0; num != 0; i++)
    {
        dec += (num % 10) * pow(srcBase, i);
        num /= 10;
    }
    for (int left = 1; dec != 0;)
    {
        left = dec % desBase;
        dec /= desBase;
        s = (char *)realloc(s, sizeof(char) * (len + 1));
        s[len++] = (left < 9 ? left + '0' : left - 10 + 'A');
    }
    s[len] = '\0';
    strrev(s);
    return s;
}

int main(void)
{
    int desBase, srcBase, num;
    cin >> desBase >> srcBase >> num;
    cout << numConvert(desBase, srcBase, num);
    return 0;
}