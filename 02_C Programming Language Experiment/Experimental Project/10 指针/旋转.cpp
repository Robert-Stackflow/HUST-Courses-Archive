//�������ڣ�����Ҫ�ҳ�ÿһ�������±�ı仯���ɣ�����ϵ����
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
arryTemp[j][3 - i] = arry[i][j];  //������˫��forѭ������Ϊ��һ�乫ʽ��ʵ��
}
//arryTemp[j][3] = arry[0][j]; //����1,2,3,4��ԭ������ת��Ϊ�¾��ε��±�任��ʽ
//arryTemp[j][2] = arry[1][j]; //����5,6,7,8��ԭ������ת��Ϊ�¾��ε��±�任��ʽ
//arryTemp[j][1] = arry[2][j]; //....
//arryTemp[j][0] = arry[3][j]; //....
}
printf("\n");
printf("\n");
printf("��ʼ����������ͼ��Ϊ:\n");
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
printf("��ת���������ͼ��Ϊ:\n");

for (int i = 0; i < N;i++)
{
for (int j = 0; j < N; j++)
{
printf("%-4d", arryTemp[i][j]);
}
printf("\n");
}  
};
