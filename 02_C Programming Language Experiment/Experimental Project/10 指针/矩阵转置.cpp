/*
дһ��������һ��3x3�����;���ת�ã���ָ��ʵ��
*/
#include <stdio.h>
#include <stdlib.h>
#define SIZE 3

int main()
{
����int **a = (int **)malloc(sizeof(int *)*SIZE);//��ά���鶯̬�����ڴ�
����int i,j,t;
����for(i=0; i<SIZE; i++)
��������*(a+i) = (int *)malloc(sizeof(int)*SIZE);//��ά���鶯̬�����ڴ�

����printf("����������Ԫ�أ�");
����for(i=0; i<SIZE; i++)
����for(j=0; j<SIZE; j++)
����scanf("%d",*(a+i)+j);

����for(i=0; i<SIZE; i++)//�Ծ������ת��
��������for(j=i; j<SIZE; j++)
��������{
������������t = *(*(a+i)+j);
������������*(*(a+i)+j) = *(*(a+j)+i);
������������*(*(a+j)+i) = t;
��������}

����printf("ת��֮��Ϊ��");
����for(i=0; i<SIZE; i++)
��������for(j=0; j<SIZE; j++)
������������printf("%d ",*(*(a+i)+j));
����printf("\n");

����return 0;
}
