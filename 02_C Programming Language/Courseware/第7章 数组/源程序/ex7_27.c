#include "stdio.h"
#include "string.h"
#define SIZE 100
void push(char c);	/*��ջ����*/
void pop(void);		/*��ջ����*/
char stack[SIZE];	/*�����ջ*/
char out[SIZE];		/*����沨�����е�����*/
int top=-1,j=0;		/*top���±���ʽ��ջָ��*/
int main(void)
{	char in[]="15+21*(41-12)-1128/12";/*�������׺���ʽ*/
	int i=0;
	memset(out,' ', SIZE);/*ȫ����ʼ��Ϊ�ո�*/
	while(in[i]!='\0')
	{
		switch(in[i])
		{
		case '0': case '1': case '2': case '3': case '4': case '5': 
case '6': case '7': case '8': case '9':
			out[j]=in[i]; /*�����ַ�ֱ�ӽ����沨������*/
			j++;
			break;
		case '+': case '-':	/*�Ӽ����㴦��*/
			j++;			/*���������кͲ�����֮�����ո�*/
			pop();			/*��ջ*/
			push(in[i]);	/*��ջ*/
			break;
		case '*': case '/':	/*�˳����㴦��*/
			j++;			/*���������кͲ�����֮�����ո�*/
			if(stack[top]=='+'||stack[top]=='-')/*���ջ������������ȼ�*/
				push(in[i]);		/*�ȵ�ǰ�������,��ǰ�����ѹջ*/
			else
				pop();/*����ǳ˻���������ȼ������ڵ�ǰ���������ջ*/
			break;
		case '(':			/*��Բ���Ŵ���*/
			push(in[i]);	/*��Բ����'('ֱ����ջ*/
			break;			
		case ')':			/*��Բ���Ŵ���*/
			pop();			/*ջ�е���Բ����'('Ϊֹ��������������ε���*/
			top--;		/*����ջ�е���Բ����'('*/
			break;
		default:
			printf("illegal input!\n");	/*�����Ƿ��ַ�������*/
			return -1;
		}
		i++; //�ƶ�����һ���ַ�
	}
	pop();			/*ջ��ʣ�������ȫ�����γ�ջ*/
	out[j]='\0';	/*�γ��沨���ַ���*/
	printf("%s\n",out);	/*����沨���ַ���*/
	return 0;
}
void push(char c) /*�����c��ջ����*/
{
	top++;
	stack[top]=c;
}
void pop(void)	/*��ջ�㷨�����ջ������Բ���ţ�����������γ�ջ*/
{				/*ֱ��������Բ����Ϊֹ; ����ջ�����в�����ȫ����ջ*/
	while(top>=0&&stack[top]!='(')
	{
		j++;
		out[j]=stack[top];
		top--;j++;
	}
	if(top==-1)	/*�����ջ�ף�����ո�����һ�������ֿ�*/
		j++;
}
