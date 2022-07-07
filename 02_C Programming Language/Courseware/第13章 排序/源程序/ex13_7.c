#include<stdio.h>
#include<string.h>
#include<stdlib.h>     /* itoa���������������� */
#include<assert.h>     /* assert�������ж��� */
#define  MAXN   50     /* ����nֵ */
char num[MAXN][100];   /* ÿ�д洢һ��������Ӧ���ַ��� */
void ShellSort(void  *x,int n, int size,int (*fcmp)(const void *,const void *)) ;
int cmp( const void *s, const void *t);
void swap (char *a,char *b,int width);

int main()
{        
	int n,i,temp;
	printf("Input n:");
    scanf( "%d", &n); 
	assert(n>0&&n<=MAXN);	/* ���� */
	printf("Input %d integers:\n",n);
	for( i = 0; i < n; i ++) 
	{
		scanf("%d",&temp);    /* ��������*/
		itoa(temp,num[i],10); /* ת��Ϊ�ַ��������ά����nums��*/
	}

	ShellSort( num, n, sizeof(num[0]), cmp);  /* ���� */    

	for(i=0;i<n;i++)                /*���*/
		printf( "%s", num[i]);   
	printf("\n");    
	return 0;
}

/************************************************************************************
�������ƣ�ShellSort
�������ܣ� ϣ������ 
����������
        x--�����������׵�ַ
        n--�����д�����Ԫ������ 
        size--��Ԫ�ص�ռ�ÿռ��С 
        fcmp--ָ������ָ�룬����ȷ�������˳��
��������ֵ����
*/
void ShellSort(void  *x,int n, int size,int (*fcmp)(const void *,const void *)) 
{
	int gap,i,gapwidth;
	char *q,*p;

	p=(char *)x;   /* �׵�ַ */
	for(gap=n/2;gap>0;gap=gap/2) 	/* ��ʼ���Ϊn/2���Ժ�ÿ�˼����Сһ�� */
	     for(i=gap;i<n;i++) /*  �ֱ�Ը�С����в������� */
		 {
			 /*  ��һ����Ϊgap��Ԫ�ؽ��в�������   */
			 gapwidth=gap*size;  /* gap��Ԫ�ص����ֽ��� */
			 for(q=p+(i-gap)*size;q>=p&&fcmp(q,q+gapwidth)<0;q-=gapwidth) 
				swap(q,q+gapwidth,size);
		 }
}

/************************************************************************************
�������ƣ�cmp
�������ܣ� �Ƚ�s��t����ȷ�������˳�� 
����������
        s �� ָ����Ƚϵĵ�һ��Ԫ�ص�ָ��.
        t ��ָ����Ƚϵĵڶ���Ԫ�ص�ָ��.��
��������ֵ����s+t>t+s,����1��s+t<t+s ����-1,s+t=t+s ����0��
************************************************************************************/
int cmp( const void *s, const void *t)
{    
	char s1[500], s2[500];   
	strcpy( s1, s);    
	strcat( s1, t);   /* s1=s+t */  
	strcpy( s2, t);   
	strcat( s2, s);   /* s2=t+s */  
	return strcmp(s1,s2);
}

/************************************************************************************
�������ƣ�swap
�������ܣ� ������Ԫ�ء� 
����������
        a �� ָ��������ĵ�һ��Ԫ�ص�ָ��.
        b ��ָ��������ĵڶ���Ԫ�ص�ָ��.��
       width--Ԫ��ռ�ÿռ��С 
��������ֵ���ޡ�
************************************************************************************/
void swap (char *a,char *b,int width)
{
     char tmp;

     if ( a != b )
        while ( width-- ) {
             tmp = *a;
             *a++ = *b;
             *b++ = tmp;
         }
}

