#include<stdio.h> 
#include<string.h>
/*����������
xiaoming 90
xiaohong 78
xiaogang 83*/ 
/*������
xming 80 
jerry 89 
xhong 80 
angel 87 */
/*
1
4
xming 80
jerry 89
xhong 80
angel 87
2
4
80
xming 80
xhong 80
*/
//�������� 
void bubble_sort(char a[][10],int b[],int s); 
int search(int score[],int check,int number);
int main(void)
{
	int  flag=1;
	int  score[1000];
	int  number; 
	char name[1000][10];
	while(flag!=0)
	{
	scanf("%d",&flag);
	if(flag==1)
	{
	scanf("%d",&number); 
	for(int i=0;i<number;i++)
	{		
		scanf("%s",&name[i]);
        scanf("%d",&score[i]);
	}
	}
	if(flag==2)
		bubble_sort(name,score,number);
	if(flag==3)
	{
    for(int i=0;i<number;i++)
    {                     
    	printf("%s ",name[i]);
    	printf("%d\n",score[i]); 	
	}	
	}
	if(flag==4)
	{
	int check;
	scanf("%d",&check);
	int i=0,j=number-1,flag=0,k,result[10],p,q;
	while(i<=j)
	{//���ֲ��� 
	k=(i+j)/2;
	if(check>score[k])	j=k-1;
	else if(check<score[k])	i=k+1;
	else{
		//���ҵ���һ�������ֵʱ����ǰ������Ѱ������������ֵ 
        q=p=k;
        while(score[--p]==check);
        while(score[++q]==check);
        flag=1;
        break;
	}
	}
	if(flag==0) printf("not found");
	//flag==0��Ҳ��û���ҵ��óɼ� 
	else 
	{	
	for(int j=p+1;j<q;j++)
	{//����Ƚ����ֵ���ĸ˳�򣬲�����ĸ˳��ǰ������ͨ�������������ƶ� 
			for(int i=0;i<4&&j<q-1;i++)
			{
				if(name[j][i]>name[j+1][i])
				{
				printf("enter!\n");
				char m[20];
                strcpy(m,name[j]);
                strcpy(name[j],name[j+1]);
                strcpy(name[j+1],m);
				break;
				}
				else break;
			}	
			//������������ĳɼ������� 
		printf("%s %d\n",name[j],score[j]);
	}	
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
			{
				m[j][k]=a[j][k];
				a[j][k]=a[j+1][k];
				a[j+1][k]=m[j][k];	
			}
		}
		if(b[j]==b[j+1])	
		{
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
