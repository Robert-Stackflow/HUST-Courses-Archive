#include "stdio.h"
#define SIZE 1000
void push(int n);	/*压栈操作*/
int pop(void);		/*出栈操作*/
int stack[SIZE];	/*将数组作为值栈使用*/
int top=-1;			/*下标作为栈顶"指针"*/
int main(void)
{	char ch,ch1;
	int i=0,n=0,right_oprand;/* right_oprand为右操作数 */
	ch=ch1='\0';
	while((ch1=ch,ch=getchar())!=EOF)
	{		
		switch(ch)
		{
		case '0': case '1': case '2': case '3': case '4': case '5': \
case '6': case '7': case '8': case '9':	/*ch为数字字符*/
			n=n*10+(ch-'0'); /*将数字字符串转换成为对应整数*/
			break;
		case ' ':			/*ch等于空格*/
		case '\n':
			switch(ch1)
			{
			case '+':
				right_oprand=pop();/*右操作数出栈*/
				push(pop()+right_oprand);/*被加数出栈加加数，和再压栈*/
				break;
			case '-':
				right_oprand=pop();/*右操作数出栈*/
				push(pop()-right_oprand);/*被减数出栈减减数，差再压栈*/
				break;
			case '*':
				right_oprand=pop();/*右操作数出栈*/
				push(pop()*right_oprand);/*被乘数出栈乘以乘数，积再压栈*/
				break;
			case '/':
				right_oprand=pop();/*右操作数出栈*/
				if(right_oprand)/*除数为零吗*/
					push(pop()/right_oprand);/*除数非零，做除法，商再压栈*/
				else
				{
					printf("divide by zero!");/*输出除数为零*/
					return -1;/*返回异常*/
				}
				break;
			case ' ':
				break;
			default:
				push(n);/*操作数压栈*/
				n=0;
			}
		case '+': case '-': case '*': case '/': 
			break;
		default:
			printf("illegal input!\n");
					return -1;
		}
	}
	printf("result is %d\n",pop());	/*输出运算结果*/
	return 0;
}
void push(int n)
{	top++;	/*栈指针指向待压单元*/
	stack[top]=n;/*数据入栈*/
}
int pop(void)
{	int x;
	x=stack[top];/*栈顶元素值赋给x*/
	top--;/*栈指针减1，指向下一单元*/
	return x;/*返回栈顶元素值*/
}

