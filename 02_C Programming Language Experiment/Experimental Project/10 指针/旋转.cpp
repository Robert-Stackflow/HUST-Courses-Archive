//技巧所在：就是要找出每一个数组下标的变化规律，相联系规律
#include <stdio.h>
#define N 4


int main(void)
{
int i, j;
int arryTemp[N][N] = { 0 };
int arry[N][N] = {
{ 1, 2, 3, 4 },
{ 5, 6, 7, 8 },
{ 9, 10, 11, 12 },
{ 13, 14, 15, 16 }
};
for (int j = 0; j < N; j++)
{
for (int i = 0; i < N; i++)
{
arryTemp[j][3 - i] = arry[i][j];  //可以用双重for循环，简化为这一句公式来实现
}
//arryTemp[j][3] = arry[0][j]; //这是1,2,3,4由原来矩形转换为新矩形的下标变换公式
//arryTemp[j][2] = arry[1][j]; //这是5,6,7,8由原来矩形转换为新矩形的下标变换公式
//arryTemp[j][1] = arry[2][j]; //....
//arryTemp[j][0] = arry[3][j]; //....
}
printf("\n");
printf("\n");
printf("初始化矩形数组图形为:\n");
for (int i = 0; i < N; i++)
{
for (int j = 0; j < N; j++)
{
printf("%-4d", arry[i][j]);
}
printf("\n");
}


printf("\n");
printf("\n");
printf("=====================");
printf("\n");
printf("\n");
printf("旋转后矩形数组图形为:\n");

for (int i = 0; i < N;i++)
{
for (int j = 0; j < N; j++)
{
printf("%-4d", arryTemp[i][j]);
}
printf("\n");
}  
};
