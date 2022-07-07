#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;
class DICT
{
    char **const words; //存放单词
    const int max;      //字典可以存放单词的个数
    int pos;            //当前可以存放单词的空闲位置
public:
    DICT(int max);       // max为最大单词个数
    DICT(const DICT &d); //深拷贝构造
    DICT(DICT &&d)
    noexcept;                                         //移动构造
    virtual ~DICT() noexcept;                         //析构
    virtual DICT &operator=(const DICT &d);           //深拷贝赋值
    virtual DICT &operator=(const DICT &&d) noexcept; //移动赋值
    virtual int operator()(const char *word) const;   //查找单词位置,-1表示没找到
    virtual DICT &operator<<(const char *word);       //若字典中没有该单词则加入
    virtual DICT &operator>>(const char *word);       //删除字典中的这个单词,后面的单词往前移动
                                                      //字典中的单词保持连续存放
    virtual const char *operator[](int n) const;      //取出第n(n>=0)个单词
};
DICT::DICT(int max) : words(new char *[max]), max(max), pos(0) {}
DICT::DICT(const DICT &d) : words(new char *[max]), max(max), pos(0)
{
    *(const_cast<int *>(&max)) = d.max;
    *(const_cast<int *>(&pos)) = d.pos;
    char ***temp = const_cast<char ***>(&words);
    for (int i = 0; i < d.pos; i++)
        *(*temp + i) = d.words[i];
}
DICT::DICT(DICT &&d) noexcept : words(new char *[max]), max(max), pos(0)
{
    pos = d.pos;
    *(const_cast<int *>(&max)) = d.max;
    *(const_cast<char ***>(&words)) = d.words;
    *(const_cast<char ***>(&d.words)) = NULL;
    *(const_cast<int *>(&d.max)) = 0;
    d.pos = 0;
}
DICT::~DICT()
{
    if (words)
    {
        for (int i = 0; i < pos; i++)
            delete words[i];
        delete words;
        *(const_cast<char ***>(&words)) = 0;
    }
}
DICT &DICT::operator=(const DICT &d)
{
    *(const_cast<int *>(&max)) = d.max;
    *(const_cast<int *>(&pos)) = d.pos;
    char ***temp = const_cast<char ***>(&words);
    for (int i = 0; i < d.pos; i++)
        *(*temp + i) = d.words[i];
}
DICT &DICT::operator=(const DICT &&d) noexcept
{
    pos = d.pos;
    *(const_cast<int *>(&max)) = d.max;
    *(const_cast<char ***>(&words)) = d.words;
    *(const_cast<char ***>(&d.words)) = NULL;
    *(const_cast<int *>(&d.max)) = 0;
    *(const_cast<int *>(&d.pos)) = 0;
}
int DICT::operator()(const char *word) const
{
    for (int i = 0; i < pos; i++)
    {
        if (strcmp(*(words + i), word) == 0)
            return i;
    }
    return -1;
}
DICT &DICT::operator<<(const char *word)
{
    if (this->operator()(word) == -1)
    {
        if (pos <= max)
        {
            char ***temp = const_cast<char ***>(&words);
            *(*temp + pos) = (char *)word;
            pos++;
        }
    }
}
DICT &DICT::operator<<(const char *word)
{
    int flag = this->operator()(word);
    if (flag != -1)
    {
        char ***temp = const_cast<char ***>(&words);
        for (int i = flag; i < pos; i++)
        {
            *(*temp + i) = *(*temp + i + 1);
        }
        pos--;
    }
}
const char *DICT::operator[](int n) const
{
    if (n < pos)
        return *(words + n);
}
int main(void)
{
    return 0;
}
