#include "stdio.h"
#include "string.h"
#define SIZE 100
void push(char c);	/*入栈操作*/
void pop(void);		/*出栈操作*/
char stack[SIZE];	/*运算符栈*/
char out[SIZE];		/*存放逆波兰序列的数组*/
int top=-1,j=0;		/*top：下标形式的栈指针*/
int main(void)
{	char in[]="15+21*(41-12)-1128/12";/*输入的中缀表达式*/
	int i=0;
	memset(out,' ', SIZE);/*全部初始化为空格*/
	while(in[i]!='\0')
	{
		switch(in[i])
		{
		case '0': case '1': case '2': case '3': case '4': case '5': 
case '6': case '7': case '8': case '9':
			out[j]=in[i]; /*数字字符直接进入逆波兰序列*/
			j++;
			break;
		case '+': case '-':	/*加减运算处理*/
			j++;			/*在数字序列和操作符之间插入空格*/
			pop();			/*出栈*/
			push(in[i]);	/*入栈*/
			break;
		case '*': case '/':	/*乘除运算处理*/
			j++;			/*在数字序列和操作符之间插入空格*/
			if(stack[top]=='+'||stack[top]=='-')/*如果栈顶运算符的优先级*/
				push(in[i]);		/*比当前运算符低,则当前运算符压栈*/
			else
				pop();/*如果是乘或除，即优先级不低于当前运算符，出栈*/
			break;
		case '(':			/*左圆括号处理*/
			push(in[i]);	/*左圆括号'('直接入栈*/
			break;			
		case ')':			/*右圆括号处理*/
			pop();			/*栈中到左圆括号'('为止的所有运算符依次弹出*/
			top--;		/*跳过栈中的左圆括号'('*/
			break;
		default:
			printf("illegal input!\n");	/*遇到非法字符，返回*/
			return -1;
		}
		i++; //移动到下一个字符
	}
	pop();			/*栈中剩余运算符全部依次出栈*/
	out[j]='\0';	/*形成逆波兰字符串*/
	printf("%s\n",out);	/*输出逆波兰字符串*/
	return 0;
}
void push(char c) /*运算符c入栈操作*/
{
	top++;
	stack[top]=c;
}
void pop(void)	/*出栈算法：如果栈内有左圆括号，则运算符依次出栈*/
{				/*直到遇到左圆括号为止; 否则，栈内所有操作符全部出栈*/
	while(top>=0&&stack[top]!='(')
	{
		j++;
		out[j]=stack[top];
		top--;j++;
	}
	if(top==-1)	/*如果到栈底，插入空格，与下一操作数分开*/
		j++;
}
