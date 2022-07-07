#ifndef _STACK_H
#define _STACK_H
#include "QUEUE.h"
class STACK : public QUEUE
{
    QUEUE q;

public:
    STACK(int m);          //��ʼ��ջ�������2m-2��Ԫ��
    STACK(const STACK& s); //��ջs�����ʼ��ջ
    STACK(STACK&& s)
        noexcept;                             //��ջs�ƶ�������ʼ��ջ
    int size() const noexcept;            //����ջ��������2m
    operator int() const noexcept;        //����ջ��ʵ��Ԫ�ظ���
    STACK& operator<<(int e);             //��e��ջ�������ص�ǰջ
    STACK& operator>>(int& e);            //��ջ��e�������ص�ǰջ
    STACK& operator=(const STACK& s);     //�����ֵ�����ر���ֵջ
    STACK& operator=(STACK&& s) noexcept; //�ƶ���ֵ�����ر���ֵջ
    char* print(char* b) const noexcept;  //��ջ�׵�ջ����ӡջԪ��
    ~STACK() noexcept;                    //����ջ
};
#endif