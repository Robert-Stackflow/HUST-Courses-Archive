#include <stdio.h>
#include <stdlib.h>
struct s_list{
    char data;
    struct s_list *next;
};
struct s_list* create_list(char *p);
int abs(int x);
int main(void)
{
    struct s_list *head =NULL, *p;
    char s[100];
    scanf("%s",s);
    head=create_list(s);
    p=head;
    while(p){
        printf("%c ",p->data);
        p=p->next;
    }     
    printf("\n");
    printf("%s\n",s);
    p=head;
    struct s_list *best =head;
    char cx=0;
    while(cx==0||cx=='\n'){
        scanf("%c",&cx);
    }
    while(p){
        if(abs(best->data-cx)>abs(p->data-cx)){
            best=p;
        }
        p=p->next;
    }
    if(best->data!=cx){
        struct s_list *now=(struct s_list *)malloc(sizeof(struct s_list));
        now->data=cx;
        now->next=best->next;
        best->next=now;
    }
    else{
        struct s_list *before=NULL;
        p=head;
        if(p->data!=cx){
            while(p){
            if(p->next==best){
                before=p;
            }
            p=p->next;
        }
        before->next=best->next;
        }
        else{
            head=head->next;
        }
    }
    p=head;
    while(p){
        printf("%c",p->data);
        p=p->next;
    }
    return 0;
}

struct s_list* create_list(char *p){
    struct s_list *loc_head=NULL,*tail;
    if(p[0]==0);
    else{
        loc_head=(struct s_list *)malloc(sizeof(struct s_list));
        loc_head->data=*p++;
        tail=loc_head;
        while(*p){
            tail->next=(struct s_list *)malloc(sizeof(struct s_list));
            tail=tail->next;
            tail->data=*p++;
        }
        tail->next=NULL;
    }
    return loc_head;
}
int abs(int x){
    return x>0?x:-x;
}

