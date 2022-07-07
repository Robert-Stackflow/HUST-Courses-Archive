#include <stdio.h>
#include <stdlib.h>
#define N 100
typedef int ElemType;
typedef struct TWSTACK {
     ElemType elem[N];
     int top1,top2;
     } TWSTACK;
int inistack(TWSTACK &S);
int push(TWSTACK &S,int i,ElemType e);
int pop(TWSTACK &S,int i,ElemType &e);
int main()
{
int  i,f,e1,e2;
TWSTACK S;
scanf("%d",&f);
switch(f)
{
case 0: inistack(S);
      if (S.top1==0&& S.top2==N-1) printf("OK");
      else printf("初始化失败");
		break;
case 1:	S.top1=rand()%N;
		S.top2=S.top1-1;
      if (push(S,1,10))
      		{  printf("栈1入栈时未判满");break;}
		S.top1=rand()%N;
		S.top2=S.top1-1;
      if (push(S,2,10))
      		{  printf("栈2入栈时未判满");break;}
      S.top1=rand()%N;
		S.top2=S.top1;
      e1=rand();
      if (push(S,1,e1)==0 || S.top1!=S.top2+1|| S.elem[S.top1-1]!=e1)
      		{  printf("栈1入栈时有错");break;}
      S.top1=rand()%N;
		S.top2=S.top1;
      if (push(S,2,e1)==0 || S.top1!=S.top2+1 || S.elem[S.top2+1]!=e1)
      		{  printf("栈2入栈时有错");break;}
      printf("OK");
		break;
case 2: S.top1=0;
      S.top2=N-1;
      if (pop(S,1,e1) || pop(S,2,e1))
      	{  printf("出栈时未判空");break;}
      e1=rand();
      push(S,1,e1);
     if (pop(S,1,e2)==0 || e1!=e2) {printf("%d %d栈1出栈有错",pop(S,1,e2),e1!=e2);break;}
      e1=rand();
      push(S,2,e1);
     if (pop(S,2,e2)==0 || e1!=e2) {printf("栈2出栈有错");break;}
       printf("OK");
		break;
case 3: i=1;
	   inistack(S);
      scanf("%d",&f);
      while (f)
      {
      	if (f==1) push(S,1,i++);
       else pop(S,1,e1);
	     scanf("%d",&f);
      }
      for(i=0;i<S.top1;i++)
      	printf(" %d",S.elem[i]);
}
return 1;
}
int inistack(TWSTACK &S)
{//该函数实现初始化S，得到2个空栈。
//根据双向栈的示意图，理解初始化要求。
    S.top1=0;
	S.top2=N-1;
}
int push(TWSTACK &S,int i,ElemType e)
{//i取值1或2，分别对应左或右栈，将元素e压入S的对应栈。
//成功入栈返回1，否则返回0
	if(i==1)
	{
		if(S.top1>S.top2) return 0;
		else S.elem[S.top1]=e;
		S.top1++;
    }
    else
    {
    	if(S.top1>S.top2) return 0;
		else S.elem[S.top2]=e;
		S.top2--;
	}
    return 1;
}
int pop(TWSTACK &S,int i,ElemType &e)
{////i取值1或2，分别对应左或右栈，将S对应栈的栈顶元素出栈，赋值给e。
//成功出栈返回1，否则返回0
	if(i==1)
	{
		if(S.top1==0) return 0;
		e=S.elem[S.top1-1];
		S.top1--;
	}
	else
	{
		if(S.top2==N-1) return 0;
		e=S.elem[S.top2+1];
		S.top2++;
	}
	return 1;
}
