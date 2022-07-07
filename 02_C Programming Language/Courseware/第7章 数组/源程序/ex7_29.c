#include "stdio.h"
#define SIZE 1000
void push(int n);	/*ѹջ����*/
int pop(void);		/*��ջ����*/
int stack[SIZE];	/*��������Ϊֵջʹ��*/
int top=-1;			/*�±���Ϊջ��"ָ��"*/
int main(void)
{	char ch,ch1;
	int i=0,n=0,right_oprand;/* right_oprandΪ�Ҳ����� */
	ch=ch1='\0';
	while((ch1=ch,ch=getchar())!=EOF)
	{		
		switch(ch)
		{
		case '0': case '1': case '2': case '3': case '4': case '5': \
case '6': case '7': case '8': case '9':	/*chΪ�����ַ�*/
			n=n*10+(ch-'0'); /*�������ַ���ת����Ϊ��Ӧ����*/
			break;
		case ' ':			/*ch���ڿո�*/
		case '\n':
			switch(ch1)
			{
			case '+':
				right_oprand=pop();/*�Ҳ�������ջ*/
				push(pop()+right_oprand);/*��������ջ�Ӽ���������ѹջ*/
				break;
			case '-':
				right_oprand=pop();/*�Ҳ�������ջ*/
				push(pop()-right_oprand);/*��������ջ������������ѹջ*/
				break;
			case '*':
				right_oprand=pop();/*�Ҳ�������ջ*/
				push(pop()*right_oprand);/*��������ջ���Գ���������ѹջ*/
				break;
			case '/':
				right_oprand=pop();/*�Ҳ�������ջ*/
				if(right_oprand)/*����Ϊ����*/
					push(pop()/right_oprand);/*�������㣬������������ѹջ*/
				else
				{
					printf("divide by zero!");/*�������Ϊ��*/
					return -1;/*�����쳣*/
				}
				break;
			case ' ':
				break;
			default:
				push(n);/*������ѹջ*/
				n=0;
			}
		case '+': case '-': case '*': case '/': 
			break;
		default:
			printf("illegal input!\n");
					return -1;
		}
	}
	printf("result is %d\n",pop());	/*���������*/
	return 0;
}
void push(int n)
{	top++;	/*ջָ��ָ���ѹ��Ԫ*/
	stack[top]=n;/*������ջ*/
}
int pop(void)
{	int x;
	x=stack[top];/*ջ��Ԫ��ֵ����x*/
	top--;/*ջָ���1��ָ����һ��Ԫ*/
	return x;/*����ջ��Ԫ��ֵ*/
}

