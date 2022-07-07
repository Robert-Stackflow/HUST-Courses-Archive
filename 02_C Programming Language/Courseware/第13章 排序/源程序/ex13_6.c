/*���˻ά�ư�  */
#include<stdio.h>
#include<string.h>

struct medal
{
   char name[10];  /* �������� */
   int  gold;      /* ������   */
   int  sliv;      /* ������   */
   int  bron;      /* ͭ����   */
};

void Display(struct medal c[],int n);      /* �б���ʾ����������Ϣ */
void ShellSort(void  *x,int n, int size,int (*fcmp)(const void *,const void *));
int cmp( const void *s, const void *t);
void swap (char *a,char *b,int width);

int main()
{

	struct medal country[10]={
		{"Japan",1,3,1},
		{"America",8,3,1},
		{"Germany",2,5,6},
		{"England",3,2,5},
		{"France",4,8,6},
		{"Canada",2,6,0},
		{"Korea",5,3,6},
		{"Australia",3,2,6},
		{"India",1,3,1},
		{"China",8,3,1}
	};
	ShellSort(country,10,sizeof(country[0]),cmp);
    Display(country,10);
	return 0;
}

/***********************************************************************
�������ƣ� Display
�������ܣ��б���ʾ����������Ϣ
����������
          c����Ÿ���������Ϣ������
		  n ��������������
��������ֵ���ޡ�
************************************************************************/
void Display(struct medal c[],int n )
{
    int i;
    printf("\n    ����       ����    ����    ͭ��    \n");
    for(i=0;i<n;i++)
		printf("%10s%8d%8d%8d\n",c[i].name,c[i].gold,c[i].sliv,c[i].bron);
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
************************************************************************************/
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
/***********************************************************************
�������ƣ�cmp
�������ܣ���ؼ��ֱȽϡ�
����������
          s��ָ����Ƚϵĵ�1�����ҵ���Ϣ
          t��ָ����Ƚϵĵ�2�����ҵ���Ϣ
��������ֵ��s�Ľ��ƶ࣬����������s�Ľ����٣����ظ�����
            ����һ��ʱ��s�����ư��ֵ�����t��ǰ�棬�������������򣬷��ظ�����
************************************************************************/
int cmp( const void *s, const void *t)
{    
	struct medal *a,*b;
	a=(struct medal *)s;
	b=(struct medal *)t;
	if(a->gold!=b->gold)    /* �ȽϽ����� */
		return a->gold-b->gold;  
	if(a->sliv!=b->sliv)     /* �Ƚ������� */
		return a->sliv-b->sliv;
	if(a-> bron!=b-> bron)   /* �Ƚ�ͭ���� */
		return a-> bron-b-> bron;
	return strcmp(b->name,a->name);  /* �ȽϹ������� */
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
