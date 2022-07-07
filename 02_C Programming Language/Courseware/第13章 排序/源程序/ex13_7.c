#include<stdio.h>
#include<string.h>
#include<stdlib.h>     /* itoa函数宏在其中声明 */
#include<assert.h>     /* assert宏在其中定义 */
#define  MAXN   50     /* 最大的n值 */
char num[MAXN][100];   /* 每行存储一个整数对应的字符串 */
void ShellSort(void  *x,int n, int size,int (*fcmp)(const void *,const void *)) ;
int cmp( const void *s, const void *t);
void swap (char *a,char *b,int width);

int main()
{        
	int n,i,temp;
	printf("Input n:");
    scanf( "%d", &n); 
	assert(n>0&&n<=MAXN);	/* 断言 */
	printf("Input %d integers:\n",n);
	for( i = 0; i < n; i ++) 
	{
		scanf("%d",&temp);    /* 输入整数*/
		itoa(temp,num[i],10); /* 转换为字符串存入二维数组nums中*/
	}

	ShellSort( num, n, sizeof(num[0]), cmp);  /* 排序 */    

	for(i=0;i<n;i++)                /*输出*/
		printf( "%s", num[i]);   
	printf("\n");    
	return 0;
}

/************************************************************************************
函数名称：ShellSort
函数功能： 希尔排序。 
函数参数：
        x--待排序数组首地址
        n--数组中待排序元素数量 
        size--各元素的占用空间大小 
        fcmp--指向函数的指针，用于确定排序的顺序
函数返回值：无
*/
void ShellSort(void  *x,int n, int size,int (*fcmp)(const void *,const void *)) 
{
	int gap,i,gapwidth;
	char *q,*p;

	p=(char *)x;   /* 首地址 */
	for(gap=n/2;gap>0;gap=gap/2) 	/* 初始间隔为n/2，以后每趟间隔缩小一半 */
	     for(i=gap;i<n;i++) /*  分别对各小组进行插入排序 */
		 {
			 /*  对一组间隔为gap的元素进行插入排序   */
			 gapwidth=gap*size;  /* gap个元素的总字节数 */
			 for(q=p+(i-gap)*size;q>=p&&fcmp(q,q+gapwidth)<0;q-=gapwidth) 
				swap(q,q+gapwidth,size);
		 }
}

/************************************************************************************
函数名称：cmp
函数功能： 比较s和t，以确定排序的顺序。 
函数参数：
        s ： 指向待比较的第一个元素的指针.
        t ：指向待比较的第二个元素的指针.。
函数返回值：是s+t>t+s,返回1，s+t<t+s 返回-1,s+t=t+s 返回0。
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
函数名称：swap
函数功能： 交换两元素。 
函数参数：
        a ： 指向待交换的第一个元素的指针.
        b ：指向待交换的第二个元素的指针.。
       width--元素占用空间大小 
函数返回值：无。
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

