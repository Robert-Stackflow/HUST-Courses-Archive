#include<stdio.h> 
//求字符串长度
//求数组元素的个数，如int类型数组，字符串长度 
//不同类型的数组的长度不同 
int main(void)
{
	char str1[]="we32";
	char str2[10],str3[15];
	printf("Input a string:\n");
	scanf("%s",str3);
	int x1,x2,x3;
	x1=sizeof(str1)/sizeof(str1[0]);
	x2=sizeof(str2)/sizeof(str2[0]);
	x3=sizeof(str3)/sizeof(str3[0]);
	printf("%d\t%d\t%d",x1,x2,x3);
	return 0;
}
