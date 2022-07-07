#include "stdio.h"
#include "stdlib.h"
typedef int data_type;
typedef struct node{
	  	data_type	data;
	  	struct node *left;
	  	struct node *right;
} node;
typedef node * b_tree;
b_tree tree(b_tree *ptree,int x);
void create_tree(b_tree *ptree);
b_tree find_tree(b_tree pnode,int x);
void preorder_traverse(b_tree root);
void inorder_traverse(b_tree root);
void postorder_traverse(b_tree root);
b_tree tree(b_tree *ptree,data_type x)
{ if(*ptree==NULL){
		  (*ptree)=(b_tree)malloc(sizeof(node));
		  (*ptree)->data=x;
		  (*ptree)->left=(*ptree)->right=NULL;
	  }
	  else{ 
		  tree(&(*ptree)->left,x-1);
		  tree(&(*ptree)->right,x+1);
	  }
printf("\t%p\t%p\t%d\t%p\n",(*ptree),(*ptree)->left, \
(*ptree)->data,(*ptree)->right);
	  return (*ptree);
}
void create_tree(b_tree *pt)
{ int x,i=1; 
	  printf("input a number of integers,end with ctrl+z\n");
	  while(scanf("%d",&x)!=EOF){
		  printf("i=%d,x=%d\n",i++,x);
		  tree(pt,x);
	  }
}
void preorder_traverse(b_tree root) /* ÏÈĞò±éÀú¶ş²æÊ÷ */
{ if(root!=NULL){
		  printf("\t%p\t%p\t%d\t%p\n ",root,root->left,root->data,root->right);
		  preorder_traverse(root->left);
		  preorder_traverse(root->right);
	  }
}
void inorder_traverse(b_tree root) /* ÖĞĞò±éÀú¶ş²æÊ÷ */
{ if(root!=NULL){
		  inorder_traverse(root->left);
		  printf("\t%p\t%p\t%d\t%p\n ",root,root->left,root->data,root->right);
		  inorder_traverse(root->right);
	  }
}
void postorder_traverse(b_tree root) /* ºóĞò±éÀú¶ş²æÊ÷ */
{ if(root!=NULL){
		  postorder_traverse(root->left);
		  postorder_traverse(root->right);
		  printf("\t%p\t%p\t%d\t%p\n ",root,root->left,root->data,root->right);
	  }
}
b_tree find_tree(b_tree pnode,data_type x)
{ if(pnode==NULL)
		  return NULL;
	  else if(x==pnode->data)
		  return (pnode);
	  else{
		  find_tree(pnode->left,x);
		  find_tree(pnode->right,x);
	  }
}
int main(void)
{	  int x;
	  b_tree root=NULL,p;
		  create_tree(&root);
	  printf("\taddr\t\tleft\t      data\tright\n ");
	  preorder_traverse(root);printf("\n");
/* inorder_traverse(root); printf("\n");	
	  postorder_traverse(root); printf("\n"); */
	  printf("input the number to find!\n");
	  scanf("%d",&x);
	  p=find_tree(root,x);
	  printf("addr: %p\tvalue: %d\n",p,p->data);
	  return 0;
}
