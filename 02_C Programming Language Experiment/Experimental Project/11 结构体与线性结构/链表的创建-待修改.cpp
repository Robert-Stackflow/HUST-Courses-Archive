#include <stdio.h>
#include <stdlib.h>
typedef struct node {
int value;
struct node * next;
}nod;
nod * create(int n);
int main()
{
    int n;
    scanf("%d",&n);
    create(n);
    nod * head1;
    head1= create(n);
    nod * p;
    for(p=head1;p!=NULL;p=p->next)
    {
        printf("%d\t",p->value);
    }
    printf("%\n");
    return 0;
}
nod *create(int n)
{
    int i;
    nod *head;
    head=(nod *)malloc(sizeof(nod));
    head->value=10;
    head->next=NULL;
    nod *pre;
    nod *cur;
    pre=head;
    for(i=1;i<n;pre=pre->next)
    {
        cur=(nod *)malloc(sizeof(nod));
        cur->value=(i+1)*10;
        cur->next=NULL;
        pre->next=cur;
    }
    return head;
}

