#include "stdio.h"
#include "stdlib.h"
int main(void)
{	char ch;
	system("dir c:\\");/*执行显示c盘根目录下文件和子目录命令，注意用"\\"*/
	printf("mycopy.exe is in root directory or not? y/n\n");
	ch=getchar();/*观察c盘根目录是否有mycopy.exe，然后按'y'或'n'*/
	getchar();/*读ch=getchar()后的换行*/
	if(ch=='Y'||ch=='y'){
		system("c:\\mycopy.exe");/*执行例10.5程序mycopy.exe*/
		printf("clear screen or not?y/n \n");
		ch=getchar();getchar();/*读ch=getchar()后的换行*/
		if(ch=='Y'||ch=='y')
			system("cls");/*执行清除屏幕命令*/
		printf("input any character to finish!\n");
		getchar();/*输入任意字符并回车将结束程序运行*/
	}
	else{/*如果c盘根目录下没有mycopy.exe，输出提示信息后返回操作系统*/
		printf("no mycopy.exeprogram in root directory!\n");
		exit(-1);
	}
	return 0;
}
