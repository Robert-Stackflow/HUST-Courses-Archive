#include<stdio.h>
//指针函数的应用——传递函数指针
//把每个单词的首字母大写/小写的函数封装
//char demo1();
char demo2();
int main(void)
{
//	char (*pdemo1)();
	char (*pdemo2)();
//	pdemo1=demo1;
	pdemo2=demo2;
//	char (*p[2])()={demo1,demo2};
	char t1,t2,t3,t4;
//	t1=pdemo1();纪念币 
//	t2=(*pdemo1)();
	t3=pdemo2();
	t4=(*pdemo2)();
	printf("%s\t%s\t%s\t%s\n",t1,t2,t3,t4);
}
//char demo1()
//{
//	char str[]="hello";
//	return str;
//}
char demo2()
{
	char *str="hello";
	return str;
}
