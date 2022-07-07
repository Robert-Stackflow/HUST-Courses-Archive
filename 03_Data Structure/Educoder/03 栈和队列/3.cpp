#include "stdio.h"
#include "string.h"
typedef char ElemType;
#define MAXLENGTH 100
#define N 100
typedef struct TWSTACK {
     ElemType elem[N];
     int top1,top2;
     } TWSTACK;
typedef struct QUEUE {
     ElemType elem[MAXLENGTH];
     int front,length;
     } QUEUE;
int inistack(TWSTACK &S);
int push(TWSTACK &S,int i,ElemType e);
int pop(TWSTACK &S,int i,ElemType &e);
int iniQueue(QUEUE &Q);
int enQueue(QUEUE &Q,ElemType e);
int deQueue(QUEUE &Q,ElemType &e);
int isPalindrome(char *str);
int main()
{
    char str[100];
    scanf("%s",str);
    printf("%s",isPalindrome(str)?"YES":"NO");
    return 0;
}
int inistack(TWSTACK &S)
{//�ú���ʵ�ֳ�ʼ��S���õ�2����ջ��
//����˫��ջ��ʾ��ͼ������ʼ��Ҫ��
    S.top1=0;
	S.top2=N-1;
}
int push(TWSTACK &S,int i,ElemType e)
{//iȡֵ1��2���ֱ��Ӧ�����ջ����Ԫ��eѹ��S�Ķ�Ӧջ��
//�ɹ���ջ����1�����򷵻�0
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
{////iȡֵ1��2���ֱ��Ӧ�����ջ����S��Ӧջ��ջ��Ԫ�س�ջ����ֵ��e��
//�ɹ���ջ����1�����򷵻�0
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
int isPalindrome(char *str)
{
	TWSTACK S;
	inistack(S);
	if(strlen(str)==1) return 0;
	for(int i=0;i<=strlen(str)/2-1;i++)
	{
		push(S,1,str[i]);
		push(S,2,str[strlen(str)-i-2]);
		if(S.elem[S.top1-1]!=S.elem[S.top2+1]) return 0;
	}
	return 1;
}
