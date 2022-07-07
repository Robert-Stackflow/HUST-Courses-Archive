#include <cstring>
#include <iostream>
using namespace std;
class STRING
{
    char *str;

public:
    int strlen() const;
    int strcmp(const STRING &s) const;
    STRING &strcpy(const STRING &s);
    STRING &strcat(const STRING &s);
    STRING(char *s);
    ~STRING();
};
STRING::STRING(char *s)
{
    if (str = new char[::strlen(s) + 1])
        ::strcpy(str, s);
}
STRING::~STRING()
{
    if (str)
    {
        delete str;
        str = nullptr;
    }
}
int STRING::strlen() const
{
    return ::strlen(str);
}
int STRING::strcmp(const STRING &s) const
{
    return ::strcmp(str, s.str);
}
STRING &STRING::strcpy(const STRING &s)
{
    if (str)
    {
        delete str;
        str = nullptr;
    }
    if (str = new char[s.strlen() + 1])
        ::strcpy(str, s.str);
    return (*this);
}
STRING &STRING::strcat(const STRING &s)
{
    str = (char *)realloc(str, sizeof(char) * (::strlen(str) + ::strlen(s.str) + 1));
    ::strcat(str, s.str);
    return (*this);
}
int main(void)
{
    char a1[] = "I like apple";
    char a2[] = " and pear";
    char a3[] = " and orange";
    STRING s1(a1);
    STRING s2(a2);
    STRING s3(a3);
    cout << "Length of s1=" << s1.strlen() << "\n";
    s1.strcat(s2).strcat(s3);
    cout << "Length of s1=" << s1.strlen() << "\n";
    s3.strcpy(s2).strcpy(s1);
    cout << "Length of s3=" << s3.strlen() << "\n";
    return 0;
}
