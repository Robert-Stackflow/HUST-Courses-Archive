#include<stdio.h> 
/*输入样例：
xiaoming 90
xiaohong 78
xiaogang 83*/ 
/*样例：
xming 80 
jerry 89 
xhong 80 
angel 87 */
//声明冒泡排序函数 
void bubble_sort(char a[][10],int b[],int s); 
int main(void)
{
	int  flag=1;
	int  score[1000];
	int  number; 
	char name[1000][10];
	while(flag!=0)
	{//使用while函数实现多次输入指令 
	scanf("%d",&flag);
	if(flag==1)
	{
	scanf("%d",&number); 
	for(int i=0;i<number;i++)
	{	//当flag的值为1时，提示输入姓名与成绩	
		scanf("%s",&name[i]);
        scanf("%d",&score[i]);
	}
	}
	if(flag==2)
	//值为2时，进行排序但并不输出 
		bubble_sort(name,score,number);
	if(flag==3)
	{//值为3时，进行输出 
    for(int i=0;i<number;i++)
    {                     
    	printf("%s ",name[i]);
    	printf("%d\n",score[i]); 	
	}	
	}
	}
	return 0;
}
void bubble_sort(char a[][10],int b[],int s)
{
	int i,j,t;
	char m[1000][10];
	for (i=0;i<s-1;i++)
	{
	for(j=0;j<s-i-1;j++)
	{
		if(b[j]<b[j+1])
		{
			t=b[j],b[j]=b[j+1],b[j+1]=t;
			for(int k=0;k<10;k++)
			{//在冒泡排序成绩时，同时对成绩对应的姓名进行交换操作 
				m[j][k]=a[j][k];
				a[j][k]=a[j+1][k];
				a[j+1][k]=m[j][k];	
			}
		}
		if(b[j]==b[j+1])	
		{//如果成绩相等，那么就比较姓名首字母，若仍相同比较下一个字母，以此类推进行排序 
			for(int i=0;i<4;i++)
			{
				if(a[j][i]>a[j+1][i])
				{
				for(int k=0;k<10;k++)
				{
				m[j][k]=a[j][k];
				a[j][k]=a[j+1][k];
				a[j+1][k]=m[j][k];	
				}
				break;
				} 
				else if(a[j][i]==a[j+1][i]) continue; 
				else break;
			}	
		}
	}
}
}
