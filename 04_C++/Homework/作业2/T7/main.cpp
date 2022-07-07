#include <cstring>
#include <iostream>
using namespace std;
class SEQUENCE;
class TREE
{
    int item; //节点的值
    TREE *left, *right;
    friend SEQUENCE;

public:
    int getNodeNum();          //返回节点总数
    int getNodes(int items[]); //将所有的节点保存到items[ ]中
};
class SEQUENCE
{
    int *items; //用于保存1个TREE中的所有节点
    int size;   // items中元素的个数
public:
    SEQUENCE(TREE &t); //将t中的所有节点保存到items所指的缓冲区
};
int TREE::getNodeNum()
{
    int l = 0, r = 0;
    if (left)
        l = left->getNodeNum();
    if (right)
        r = right->getNodeNum();
    return l + r + 1;
}
int TREE::getNodes(int items[])
{
    int order = 0;
    if (left)
        order = left->getNodes(items);
    items[order++] = TREE::item;
    if (right)
        order = order + right->getNodes(items);
    return order;
}
SEQUENCE::SEQUENCE(TREE &t)
{
    items=new int[t.getNodeNum()];
    t.getNodes(items);
}
int main(void)
{
    return 0;
}
