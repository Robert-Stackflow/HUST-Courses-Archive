#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//qwertyuiopasdfghjkl
int abs(int n){
    return n>0?n:-n;
}
typedef struct s_list
{
	char data;
	struct s_list *next;
}list; 
void create_list(list **headp,char *p);
int find_nodes(list *head,char n);
list * insert_nodes(list * head,char n,char check);
list * delete_nodes(list **headp,char n);
int main(void)
{
	list *head=NULL,*p,*nearest;
	char str[100];
	int res;
	scanf("%s",str);
	create_list(&head,str);
	p=head;
	while(p){
		printf("%c ",p->data); 
		p=p->next;
	}
	printf("\n%s\n",str);
	char check=0;
	p=head;
	nearest=head;
    while(check==0||check=='\n')
    	scanf("%c",&check);
    while(p)
	{
        if(abs(nearest->data-check)>abs(p->data-check))
            nearest=p;
        p=p->next;
    }
	if(nearest->data==check)
		delete_nodes(&head,check);
	else insert_nodes(head,nearest->data,check);	
	p=head;
	while(p){
		printf("%c",p->data); 
		p=p->next;
	}
	return 0;	
}

void create_list(list **headp,char *p)
{	list *loc_head=NULL,*tail;
	if(p[0]=='\0');
	else { 
		loc_head=(list *)malloc(sizeof(list));
		loc_head->data=*p++; 
		tail=loc_head; 
		while(*p){ 
			tail->next=(list *)malloc(sizeof(struct s_list));
			tail=tail->next; 
			tail->data=*p++; 
		}
		tail->next=NULL; 
	}
	*headp=loc_head; 
}

int find_nodes(list *head,int n)
{	list *p=head;
	if(p){ 
		if(p->data==n) return 1; 
		else
			find_nodes(p->next,n);
	}
	else return 0;
}

list * insert_nodes(list *head,char n,char check)
{	list * current=head,*after,*other;
	while(current->data !=n&&current!=NULL)
		current=current->next;
	if(!current) return NULL; 
	after=current->next;     
	other=(list *)malloc(sizeof(list));
	other->data=check;  
	if(after){	
		other->next=after;     
		current->next=other;   
	}
	else{	
		other->next=NULL;    
		current->next=other; 
	}
	return current;         
}

list * delete_nodes(list **headp,char n)
{	
	list * current=*headp,*prior=*headp;
	while(current->data!=n&&current!=NULL){ 
		prior=current;              
		current=current->next;      
	}
	if(!current)                    
		return NULL;
	if(current==*headp)           
		*headp=current->next;
	else                          
		prior->next= current->next;
	free(current);                
	return current;
}





