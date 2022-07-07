#include<stdio.h> 
#include<string.h>
void bubble_sort(char a[],int b[],int s);
void copy(char [],char []); 
void swap(char [],char []);
int main(void)
{
	char name[1000];
	int  score[1000];
	int number;
	printf("请输入学生人数："); 
	scanf("%d",&number);
	printf("请输入学生姓名以及课程成绩：\n"); 
	for(int i=0;i<number;i++)
{
        scanf("%s",&name[i]);
        scanf("%d",&score[i]);
}
	for(int i=0;i<number;i++)
{
        printf("%s\t",name[i]);
        printf("%d\n",score[i]);
}
	bubble_sort(name,score,number); 
	printf("name		score\n");
    for(int i=0;i<number;i++)                         
    printf("%s		%d\n",name[i],score[i]);
    return 0; 
}

void bubble_sort(char a[],int b[],int s)
{
	int i,j,t,k;
	char m[1000];
	for (i=0;i<s-1;i++)
	{
	for(j=0;j<s-i-1;j++)
	{
		if(b[j]<b[j+1])
		{
			t=b[j],b[j]=b[j+1],b[j+1]=t;
			swap(a[j],a[j+1]);
		}	
	}
}
}
void copy(char t[],char mid[])
{
	int i=0,k=0;
	for(;mid[k]!='\0';i++,k++)
		t[i]=mid[k];
}

void swap(char a[],char b[])
{
	char m[100];
	int i,j;
	copy(m,a[i]);
	copy(a[i],b[j]);
	copy(b[j],m);
} 
