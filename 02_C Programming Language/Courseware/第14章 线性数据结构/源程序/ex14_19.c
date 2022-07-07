#include "stdio.h"
#include "stdlib.h"
#define SIZE 1000
#define EMPTY 1
#define FULL SIZE
typedef enum boolean {FALSE,TRUE} boolean;
typedef char data_type;
typedef struct node{
	data_type	data;
	struct node *next;
} node;
typedef struct stack {
	int		length;
	node		*SP;
} stack;
void reset(stack *stk);
void push(data_type var,stack *stk);
data_type pop(stack *stk);
data_type top(const stack *stk);
boolean empty(const stack *stk);
boolean full(const stack *stk);
void reset(stack *stk)
{	node *cur;
	  	cur=(node *)malloc(sizeof(node));
	  	cur->next=NULL;
	  	stk->length=1;
	  	stk->SP=cur;
}
void push(data_type var,stack *stk)
{	 node *cur;
	  	stk->SP->data=var;
	  	cur=(node *)malloc(sizeof(node));
	  	cur->next=stk->SP;
	  	stk->SP=cur;
	  	stk->length++;
}
data_type pop(stack *stk)
{	 node *cur;
	  	data_type	x;
	  	cur=stk->SP;
	  	stk->SP=stk->SP->next;
	  	x=stk->SP->data;	
	  	stk->length--;
	  	free(cur);
	  	return x;
}
data_type top(const stack *stk)
{
	  return (stk->SP->next->data);
}
boolean empty(const stack *stk)
{
	  return ((boolean)(stk->length==EMPTY));
}
boolean full(const stack *stk)
{
	  return ((boolean)(stk->length==FULL));
}
int main(void)
{
		data_type str[]="TSUH,ygolonhceT & ecneicS retupmoC fo egelloC";
		int i;
		stack s;
		reset(&s);
		printf("In the string:\n%s\n",str);
		for(i=0;str[i];i++)
			if(!full(&s))
				push(str[i],&s);
		printf("From the stack:\n");
		while(!empty(&s))
			putchar(pop(&s));
		putchar('\n');
	    return 0;
}
