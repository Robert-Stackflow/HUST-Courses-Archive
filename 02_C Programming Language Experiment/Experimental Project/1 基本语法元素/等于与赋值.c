#include <stdio.h>
#include <stdlib.h>

int main()
{
    int age;
    printf("请输入年龄:");
    scanf("%d",&age);
    if(age=0)   
	/*当为age=x时，x为任意值均输出为可以，
	除非x为0时输出为不可以，注意等于为==*/
        printf("可以上网吧\n");
    else printf("不可以上网吧\n");
    return 0;
}
