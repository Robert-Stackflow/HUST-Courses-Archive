#ifndef _STACK_H
#define _STACK_H
#include "QUEUE.h"
class STACK : public QUEUE
{
    QUEUE q;

public:
    STACK(int m);          //初始化栈：最多存放2m-2个元素
    STACK(const STACK& s); //用栈s深拷贝初始化栈
    STACK(STACK&& s)
        noexcept;                             //用栈s移动拷贝初始化栈
    int size() const noexcept;            //返回栈的容量即2m
    operator int() const noexcept;        //返回栈的实际元素个数
    STACK& operator<<(int e);             //将e入栈，并返回当前栈
    STACK& operator>>(int& e);            //出栈到e，并返回当前栈
    STACK& operator=(const STACK& s);     //深拷贝赋值并返回被赋值栈
    STACK& operator=(STACK&& s) noexcept; //移动赋值并返回被赋值栈
    char* print(char* b) const noexcept;  //从栈底到栈顶打印栈元素
    ~STACK() noexcept;                    //销毁栈
};
#endif