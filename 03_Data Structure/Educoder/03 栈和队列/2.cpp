#include <stdio.h>
#include <stdlib.h>
typedef int ElemType;
#define MAXLENGTH 100
typedef struct QUEUE {
     ElemType elem[MAXLENGTH];
     int front,length;
     } QUEUE;
int iniQueue(QUEUE &Q);
int enQueue(QUEUE &Q,ElemType e);
int deQueue(QUEUE &Q,ElemType &e);
int main()
{
int  i,f,e1,e2;
QUEUE Q;
scanf("%d",&f);
switch(f)
{
case 0: iniQueue(Q);
      if (Q.front>=0&& Q.front<MAXLENGTH && !Q.length) printf("OK");
      else printf("初始化失败");
		break;
case 1:	Q.length=MAXLENGTH;
		Q.front=0;
      e1=rand();
		if (enQueue(Q,e1))
      		{  printf("入队时未判满");break;}
		Q.length=MAXLENGTH-1;
		if (!enQueue(Q,e1))
      		{  printf("队列容量设置不正确");break;}
		Q.length=rand()%MAXLENGTH;
		Q.front=0;
      if (enQueue(Q,e1)==0)
      		{  printf("入队返回值有错");break;}
      printf("OK");
		break;
case 2: Q.front=rand()%MAXLENGTH;
      Q.length=0;
      if (deQueue(Q,e1))
      	{  printf("出队时未判空");break;}
      e1=rand();
      enQueue(Q,e1);
      if (deQueue(Q,e2)==0 || e1!=e2) {printf("元素出队返回值进出队元素有错%d %d",e1,e2);break;}
      printf("OK");
		break;
case 3: i=1;
	   iniQueue(Q);
      scanf("%d",&f);
      while (f)
      {
      	if (f==1) enQueue(Q,i++);
       else deQueue(Q,e1);
	     scanf("%d",&f);
      }
      for(i=0;i<Q.length;i++)
      	printf(" %d",Q.elem[(Q.front+i)%MAXLENGTH]);
}
return 1;
}
int iniQueue(QUEUE &Q)
{
	Q.front=Q.length=0;
}
int enQueue(QUEUE &Q,ElemType e)
{
    if(Q.length>=MAXLENGTH)return 0;
    else
    {
		Q.elem[Q.front+Q.length]=e;
		Q.length++;
		return 1;
	}
}
int deQueue(QUEUE &Q,ElemType &e)
{
    if(Q.length==0) return 0;
    else
    {
    	e=Q.elem[Q.front];
    	Q.front=(Q.front+1)%MAXLENGTH;
    	Q.length--;
    	return 1;
	}
}
