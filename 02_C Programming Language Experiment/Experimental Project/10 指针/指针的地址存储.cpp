#include<stdio.h>
//利用指针改变变量的值 
void change(int *p){
	*p=888;
}
//利用指针地址交换变量的值 
void swap(int *p1,int *p2){
	int temp;
	temp=*p1;
	*p1=*p2;
	*p2=temp;
}
int main(void){
	int num=10;
	int num1=20;
	char c='a';
	int *p=&num;
	//指针指向是可以修改的——p=&num1;
	int *p1=&num1;
	//也可以通过赋值的方式改变指针指向——p=p1; 
	char*q=&c;
	//p是地址，*p是指向的变量 
	printf("&num:%x\tp:%x\t&p:%x\tnum:%d\t*p:%d\t*q:%c\tq:%x\n",&num,p,&p,num,*p,*q,q);
	swap(p,p1);
	printf("交换后得到：num:%d\tnum1:%d\n",num,num1);
	*p=44;//可以通过指针改变变量的值 
	printf("&num:%x\tp:%x\t&p:%x\tnum:%d\t*p:%d\t*q:%c\tq:%x\n",&num,p,&p,num,*p,*q,q);
	change(p);//也可以利用函数实现改变值的功能 
	printf("&num:%x\tp:%x\t&p:%x\tnum:%d\t*p:%d\t*q:%c\tq:%x\n",&num,p,&p,num,*p,*q,q);
	//char类型的指针也可以改变变量的值 
	*q='b';
	printf("&num:%x\tp:%x\t&p:%x\tnum:%d\t*p:%d\t*q:%c\tq:%x\n",&num,p,&p,num,*p,*q,q);
	return 0;
}
