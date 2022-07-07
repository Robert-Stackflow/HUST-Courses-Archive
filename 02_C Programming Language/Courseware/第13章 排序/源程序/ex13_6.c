/*奥运会奖牌榜  */
#include<stdio.h>
#include<string.h>

struct medal
{
   char name[10];  /* 国家名称 */
   int  gold;      /* 金牌数   */
   int  sliv;      /* 银牌数   */
   int  bron;      /* 铜牌数   */
};

void Display(struct medal c[],int n);      /* 列表显示各国奖牌信息 */
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
函数名称： Display
函数功能：列表显示各国奖牌信息
函数参数：
          c：存放各国奖牌信息的数组
		  n ：参赛国的数量
函数返回值：无。
************************************************************************/
void Display(struct medal c[],int n )
{
    int i;
    printf("\n    国家       金牌    银牌    铜牌    \n");
    for(i=0;i<n;i++)
		printf("%10s%8d%8d%8d\n",c[i].name,c[i].gold,c[i].sliv,c[i].bron);
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
************************************************************************************/
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
/***********************************************************************
函数名称：cmp
函数功能：多关键字比较。
函数参数：
          s：指向待比较的第1个国家的信息
          t：指向待比较的第2个国家的信息
函数返回值：s的奖牌多，返回正数，s的奖牌少，返回负数。
            奖牌一样时，s的名称按字典序在t的前面，返回正数，否则，返回负数，
************************************************************************/
int cmp( const void *s, const void *t)
{    
	struct medal *a,*b;
	a=(struct medal *)s;
	b=(struct medal *)t;
	if(a->gold!=b->gold)    /* 比较金牌数 */
		return a->gold-b->gold;  
	if(a->sliv!=b->sliv)     /* 比较银牌数 */
		return a->sliv-b->sliv;
	if(a-> bron!=b-> bron)   /* 比较铜牌数 */
		return a-> bron-b-> bron;
	return strcmp(b->name,a->name);  /* 比较国家名称 */
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
