#include<stdio.h>
int main(void)
{
	float num,num1;
	scanf("%f",&num);
	int number=(int)num;
	int number1,number2;
	number2=(number%10)*100+((number/10)%10)*10+number/100;
	if((num-number)*10-(int)((num-number)*10)<0.5) number1=(num-number)*10;
	//对于浮点数的小数部分进行四舍五入，防止反转后整数位错误 
	else number1=(num-number)*10+1;
	num1=number1+(float)number2/1000.0;
	printf("%.3f",num1);
}
