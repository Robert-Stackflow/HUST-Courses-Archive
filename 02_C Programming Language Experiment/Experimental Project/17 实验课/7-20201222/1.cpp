#include<stdio.h> 
#include<math.h> 
#include<string.h>
#define CHAR_BIT 8
typedef struct bits{
	unsigned int b0:1,b1:1,b2:1,b3:1,b4:1,b5:1,b6:1,b7:1;
//	unsigned int b8:1,b9:1,b10:1,b11:1,b12:1,b13:1,b14:1,b15:1; 
}Abit; //构建字段结构 
typedef union store{
	int m;
	Abit intb;
}STORE;//构建联合体，其内容一个是整型数据，另一个是字段结构 
void  f0(int b)
{
    printf("the function %d is called!\n",b);
}
void  f1(int b)
{
    printf("the function %d is called!\n",b);
}
void  f2(int b)
{
    printf("the function %d is called!\n",b);
}
void  f3(int b)
{
    printf("the function %d is called!\n",b);
}
void  f4(int b)
{
    printf("the function %d is called!\n",b);
}
void  f5(int b)
{
    printf("the function %d is called!\n",b);
}
void  f6(int b)
{
    printf("the function %d is called!\n",b);
}
void  f7(int b)
{
    printf("the function %d is called!\n",b);
}//定义八个函数 
int main(void)
{	
	void(*p_fun[8])(int b)={f0,f1,f2,f3,f4,f5,f6,f7};
	//定义一个函数指针数组，共八个元素，分别指向八个函数 
	int m,n,flag,count=0;
	scanf("%d",&m);//读取输入的整数 
	STORE usint;
	Abit *bitp;
	usint.m=m;
	//将输入的整数赋给联合体中的整型变量； 
//	printf("%u,%u,%u",sizeof(int),sizeof(STORE),sizeof(Abit)); 
	if(usint.intb.b0==1)	p_fun[0](0);
	if(usint.intb.b1==1)	p_fun[1](1);
	if(usint.intb.b2==1)	p_fun[2](2);
	if(usint.intb.b3==1)	p_fun[3](3);
	if(usint.intb.b4==1)	p_fun[4](4);
	if(usint.intb.b5==1)	p_fun[5](5);
	if(usint.intb.b6==1)	p_fun[6](6);
	if(usint.intb.b7==1)	p_fun[7](7);
	//依次判断并调用函数 
	return 0;
}



