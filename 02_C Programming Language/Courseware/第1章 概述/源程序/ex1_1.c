#include "stdio.h"				/*文件包含编译预处理命令*/
void show(char str[]);				/*函数原型说明语句*/
int main(void)					/*主函数*/
{						/*函数体开始*/
	  char name[20];			/*声明语句*/
	  printf("Input your name please!\n");	/*输出一个提示信息*/
	  gets(name);				/*读取用户从键盘输入一个字符串*/
	  printf("Hello %s!\n",name);		/*输出Hello和用户名*/
	  show(name);				/*调用show函数，程序转show 执行*/
	  return 0;				/*返回*/
}						/*函数体结束*/
void show(char str[])				/*show函数的头部*/
{						/*函数体开始*/
	  printf("This is the first program \
for %s to learn C programming!\n",str); /*上行尾的"\"是续行标志*/
}						/* 函数体结束*/
