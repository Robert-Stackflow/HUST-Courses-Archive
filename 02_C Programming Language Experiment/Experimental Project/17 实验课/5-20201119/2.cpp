#include<stdio.h> 
/*����������
xiaoming 90
xiaohong 78
xiaogang 83*/ 
/*������
xming 80 
jerry 89 
xhong 80 
angel 87 */
//����ð�������� 
void bubble_sort(char a[][10],int b[],int s); 
int main(void)
{
	int  flag=1;
	int  score[1000];
	int  number; 
	char name[1000][10];
	while(flag!=0)
	{//ʹ��while����ʵ�ֶ������ָ�� 
	scanf("%d",&flag);
	if(flag==1)
	{
	scanf("%d",&number); 
	for(int i=0;i<number;i++)
	{	//��flag��ֵΪ1ʱ����ʾ����������ɼ�	
		scanf("%s",&name[i]);
        scanf("%d",&score[i]);
	}
	}
	if(flag==2)
	//ֵΪ2ʱ���������򵫲������ 
		bubble_sort(name,score,number);
	if(flag==3)
	{//ֵΪ3ʱ��������� 
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
			{//��ð������ɼ�ʱ��ͬʱ�Գɼ���Ӧ���������н������� 
				m[j][k]=a[j][k];
				a[j][k]=a[j+1][k];
				a[j+1][k]=m[j][k];	
			}
		}
		if(b[j]==b[j+1])	
		{//����ɼ���ȣ���ô�ͱȽ���������ĸ��������ͬ�Ƚ���һ����ĸ���Դ����ƽ������� 
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
