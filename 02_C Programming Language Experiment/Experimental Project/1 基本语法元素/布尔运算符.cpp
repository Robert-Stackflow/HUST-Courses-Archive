#include<stdio.h> 
int main(void)
{
	
    int a1;
    printf("a1 = %d\n",a1=10);
    printf("------\n");
    
    int a2=0;
    printf("a2 = %d\n",a2=10);
    printf("------\n");
    
    int a3=10;
    int c1 = (a3=2);
    printf("a3 = %d\n",a3);
    printf("c1 = %d\n",c1);
    
    printf("------\n");
    
    int a4=10;
    bool c2 = (a4=0);
    //布尔类型只有0和1两个值； 
    printf("a4 = %d\n",a4);
    printf("c2 = %d\n",c2);
    printf("------\n");
    
    
    bool a5=10;
    //任何非零值被赋值给布尔类型后，都会转换为1； 
    bool c3 = (a5=3);
    printf("a5 = %d\n",a5);
    printf("c3 = %d\n",c3);
    printf("------\n");
    
    bool a6=10;
    bool c4 = (a6=-2);
    printf("a6 = %d\n",a6);
    printf("c4 = %d\n",c4);
    printf("------\n");
    
    
    bool a7=10;
    int c5 = (a7=9);
    //表达式(a7=9)的值为1； 
    printf("a7 =%d\n",a7);
    printf("c5 =%d\n",c5);
    printf("------\n");

}
