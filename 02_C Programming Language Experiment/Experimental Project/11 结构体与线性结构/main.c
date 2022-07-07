//
//  main.c
//  简单的创建链表-测试
//
//  Created by LongHu on 2020/12/21.
//  Copyright © 2020 LongHu. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct _node{
    int value;
    struct _node *next;
}Node;
//创建单向链表
void create_new_list(Node **head,int *p);
//创建一个无限输入的链表
Node * create_list(Node **pphead);
//显示所有的链表中的数据
void showAll(Node *head);
//递归法遍历链表中数据
void showAllRecu(Node *head);
int count_nodes(Node *head);
//查找数据，并且返回这个数据的地址
Node * find_first_nodes(Node *head,int n);
//查找并且修改数据，并且返回这个数据的地址
Node * change_first_data(Node * head,int findData,int newData);
//删除指定的data对应的节点，并且返回头结点的地址
Node * delete_first_nodes(Node *head,int findData);
//插入节点(在指定的数据findData之前插入newData),并且返回head的地址
Node* insert_first_nodes(Node *head,int findData,int newData);
//对链表进行选择排序
void sortLists(Node *head);

int main(int argc, const char * argv[]) {
//    int nums[100] = {1,2,3,4,5,6,7,8,9,10,0};
    Node *head= NULL;
//    Node *p = NULL;
//    create_new_list(&head, nums);
    head = create_list(&head);
    //遍历链表方法2 for循环或者while循环都可以
    showAll(head);
    
    int count = count_nodes(head);
    printf("count = %d\n",count);
    
    Node *place = find_first_nodes(head,8);
    printf("place = %p\n",place);
    
    printf("-----\n");
    Node *Pchange = change_first_data(head, 7, 100);
    showAll(head);
    printf("-----\n");
    
    head = delete_first_nodes(head, 1);
    head = delete_first_nodes(head, 2);
    head = delete_first_nodes(head, 10);
    head = delete_first_nodes(head, 100);
    showAll(head);
    printf("-----\n");
    head = insert_first_nodes(head, 2, 99);
    head = insert_first_nodes(head, 9, 199);
    head = insert_first_nodes(head, 5, 155);
    head = insert_first_nodes(head, 8, 188);
    head = insert_first_nodes(head, 99, 999);
    showAll(head);
    printf("-----\n");
    sortLists(head);
//    delete_first_nodes(head, 100);
//    showAll(head);
//    printf("-----\n");
//    delete_first_nodes(head, 5);
//    showAll(head);
//    delete_first_nodes(head, 1);
//    showAll(head);
//    delete_first_nodes(head, 10);
    
    showAll(head);
    return 0;
}
//创建一个单向链表
void create_new_list(Node **headp,int *p){
    
    Node *tail = NULL;
    Node *loc_head = (Node *)malloc(sizeof(Node));
    loc_head->value = *p++;
    tail = loc_head ; //此时 loc_head已经动态创建出来了，所有，把loc_head的值赋给tail
    
    while (*p) {
        tail->next = (Node *)malloc(sizeof(Node));
        tail = tail->next;
        tail->value = *p++;
    }
    tail->next = NULL;
    *headp = loc_head;
    
}

//记录链表的长度 个数
int count_nodes(Node *head){
    Node *p = head;
    int count = 0;
    while (p) {
        count++;
        p = p->next;
    }
    return count;
}

//查找第一个出现的的指定的元素
Node* find_first_nodes(Node *head,int n){
    //递归法
//    Node *p = head;
//    if (p) {
//        if (p->value == n) return p;
//        else
//            find_nodes(p->next, n);
//    }
    
    //for 循环法
    for (Node *p = head; p != NULL; p = p->next) {
        if (p->value == n) {
            return p; //返回找到的地址
        }
    }
    return NULL;
    
}
//查找并且改变第一个出现的的指定的元素，只需要先利用找到的那个数的地址，进行p->value = newData而已，这个函数其实返回值可以用Void
Node * change_first_data(Node * head,int n,int newData){
    
    //for 循环法
    for (Node *p = head; p != NULL; p = p->next) {
        if (p->value == n) {
            p->value = newData;
            return p;
        }
    }
    return NULL;
}


Node * delete_first_nodes(Node *head,int findData){
    //找到这个节点p1
    Node *p1 = NULL;
    Node *p2 = NULL;
    p1 = head;
    while (p1 != NULL) {
        if (p1->value != findData ) {
            p2 = p1; //p2保存p1的上一个位置
            p1 = p1->next; //p1滚动向前移动
        }else{
            break;//跳出循环就说明已经找到就是p1
        }
    }
    if (p1 != NULL) {
        //上面的代码为找到了这个目标节点p1，然后下面的代码为删除找到的节点P1，P1分两种情况，第一种情况是:非头节点，第二种情况为头结点
        if (p1 != head) {
            p2->next = p1->next; //此时跳过P1，p1就是目标，要找到的那个需要删除的节点
            free(p1); //释放删除p1
        }else{ //此时 p1 == head
            head = p1->next;
            free(p1);//删除头部
        }
    }
       
 
    return head;
}

Node* insert_first_nodes(Node *head,int findData,int newData){
    /*思路:
     1.找到findData所对应的节点p1,与find_first_nodes函数相同
     2.新建一个pnew节点，插入到p1之前
     3.插入:p1有两种情况，1.p1是头指针 2.中间指针
     */
    //1.找到findData所对应的节点p1,与find_first_nodes函数相同
    Node *p1 = NULL;
    Node *p2 = NULL;
    p1 = head;
    while (p1 != NULL) {
        if (p1->value != findData ) {
            p2 = p1; //p2保存p1的上一个位置
            p1 = p1->next; //p1滚动向前移动
        }else{
            break;//跳出循环就说明已经找到就是p1
        }
    }
    //2.新建一个pnew节点，准备下一步将它插入到找到的p1之前
    Node *pnew = malloc(sizeof(Node));
    pnew->value = newData;
    pnew->next = NULL;
    
    if (p1 != NULL) {
        //3.插入:p1有两种情况，1.p1是头指针 2.中间指针
        if (p1 == head) {
            pnew->next = head;
            head = pnew;
        }else{
            pnew->next = p1;
            p2->next = pnew;
        }
    }
       
    
   
  
      
    return head;
}


//遍历显示
void showAll(Node *head){
    
    //遍历链表方法1 while 循环
    /*
    Node *p = head;
    while (p) {
        printf("%d\n",p->value);
        p = p->next;
    }
    */
    //for循环遍历
    for (Node *p = head; p != NULL; p = p->next) {
        printf("%d\t  %p\t%p\n",p->value,p,p->next);
    }
}
//递归遍历
void showAllRecu(Node *head){
    if (head == NULL) {
        return;
    }else{
        showAllRecu(head->next);//逆序遍历链表
        printf("%d\t  %p\t%p\n",head->value,head,head->next);
//        showAllRecu(head->next);  //正向遍历链表
    }
}

//链表的排序
void sortLists(Node *head)
{
    Node *p1 = NULL;
    Node *p2 = NULL;
    
    for(p1= head;p1!=NULL;p1=p1->next)
        for(p2=p1->next;p2!=NULL;p2=p2->next)
            if(p1->value > p2->value){
                int t;
                t=p1->value;                     /* 交换数据域,不改变指向关系 */
                p1->value = p2->value;
                p2->value = t;
            }
}

Node * create_list(Node **pphead){
    int number;
    do {
        printf("请输入一个number:\n");
        scanf("%d",&number);
        if (number != -1) {
            //add to linked-list
            Node *p = (Node *)malloc(sizeof(Node));
            p->value = number;
            p->next = NULL;
            //find the tail Node
            Node *tail = *pphead;
            if(tail){
                while (tail->next) {
                    tail = tail->next;
                }
                //attach
                tail->next = p;
            }else{
                *pphead = p;
            }
        }
    } while (number != -1);
    return *pphead;
}
