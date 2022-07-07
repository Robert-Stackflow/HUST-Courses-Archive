#ifndef QUEUE_H
#define QUEUE_H
#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include<iostream>
struct Queue
{
    int* const elems; // elems申请内存用于存放队列的元素
    const int max;    // elems申请的最大元素个数max
    int head, tail;   //队列头head和尾tail，队空head=tail;初始head=tail=0；tail指向队尾的后一位
};

void initQueue(Queue* const p, int m);               //初始化p指队列：最多申请m个元素
void initQueue(Queue* const p, const Queue& s);      //用s深拷贝初始化p指队列
void initQueue(Queue* const p, Queue&& s);           //用s移动初始化p指队列
int number(const Queue* const p);                    //返回p指队列的实际元素个数
int size(const Queue* const p);                      //返回p指队列申请的最大元素个数max
Queue* const enter(Queue* const p, int e);           //将e入队列尾部，并返回p
Queue* const leave(Queue* const p, int& e);          //从队首出元素到e，并返回p
Queue* const assign(Queue* const p, const Queue& q); //深拷贝赋s给队列并返回p
Queue* const assign(Queue* const p, Queue&& q);      //移动赋s给队列并返回p
char* print(const Queue* const p, char* s);          //打印p指队列至s并返回s
void destroyQueue(Queue* const p);                   //销毁p指向的队列
#endif