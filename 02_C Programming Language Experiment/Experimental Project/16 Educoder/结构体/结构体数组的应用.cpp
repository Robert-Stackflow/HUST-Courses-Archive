#include<stdio.h>
#define N 3
struct student{
    int num;
    char name[12];
    double score;
};
/****�����涨�庯��scan���Խṹ�����ʼ��******/
void scan(struct student *p,int n )
{
    /**********  Begin  **********/
    for(int i=0;i<n;i++)
		scanf("%d%s%lf",&(p+i)->num,(p+i)->name,&(p+i)->score);
   /**********  End  **********/
}

/****�����涨�庯��print����������ṹ����ĸ���Աֵ******/
void print(struct student *p,int n )
{
	/**********  Begin  **********/
	for(int i=0;i<n;i++)
		printf("%d %s %.1lf\n",(p+i)->num,(p+i)->name,(p+i)->score); 
	/**********  End  **********/
}
int main(void)
{
    struct student s[N];
    scan(s,N);
    print(s,N);
    return 0;
}


