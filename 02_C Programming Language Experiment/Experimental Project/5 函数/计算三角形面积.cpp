#include<math.h>
#include<stdio.h>
float Squre_Triangle(float a,float b,float c);
int main()
{
	float a,b,c,result;
    scanf("%f%f%f",&a,&b,&c);        //输入整数作为随机数种子
    result=Squre_Triangle(a,b,c);
    printf("%.3f",result);
    return 0;
}
float Squre_Triangle(float a,float b,float c)
{
	float s=(a+b+c)/2,area;
	area=sqrt(s*(s-a)*(s-b)*(s-c));
	return area;
}
