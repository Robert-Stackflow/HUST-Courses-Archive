#include<stdio.h> 
#include<string.h>
//ʵ��¼����Ʒ��Ϣ�������Ʒ��Ϣ�����۸����Ʒ����������������ɲ�ѯ��Ʒ����߼۸�
//�Ų�����������ĳ����Χ�ڵ���Ʒ�����۸�һ��ʱ����Ʒ���������˳�������
//�˵�ѡ��ȶ�����ܣ���װ�����ȹ��ܣ�Ԥ�ƴ�����200�� 
/*����������
bread ISBN2345678 6 2 2020 12 13
rice  ISBN1234566 25 3 2020 12 14
*/  
struct date{
	int year;
	int month;
	int day;
}; //�������ڽṹ��
struct article_information{
	char name[20];
	char code[20];
	int  price;
	int  quality;
	struct date prodate; 
};
int  number=2;
void bubble_sort(struct article_information shop); 
int main(void)
{
	int  flag=1; 
	struct article_information shop[number];
	while(flag!=0)
	{
	scanf("%d",&flag);
	if(flag==1)
	{
//	scanf("%d",&number); 
	for(int i=0;i<number;i++)	
		scanf("%s%s%d%d%d%d%d",&shop[i].name,&shop[i].code,&shop[i].price,&shop[i].quality,&shop[i].prodate.year,&shop[i].prodate.month,&shop[i].prodate.day);
	}
//	if(flag==2)
//		bubble_sort(*shop);
	if(flag==3)
	{
	printf("��Ʒ����\t��Ʒ��\t\t��Ʒ�۸�\t��Ʒ������\t��Ʒ��������\n");
    for(int i=0;i<number;i++)
    	printf("%s\t\t%s\t$%d\t\t%dmonths\t\t%d/%d/%d\n",shop[i].name,shop[i].code,shop[i].price,shop[i].quality,shop[i].prodate.year,shop[i].prodate.month,shop[i].prodate.day);
	}
//	if(flag==4)
//	{
//	int check;
//	scanf("%d",&check);
//	int i=0,j=number-1,flag=0,k,result[10],p,q;
//	while(i<=j)
//	{//���ֲ��� 
//	k=(i+j)/2;
//	if(check>score[k])	j=k-1;
//	else if(check<score[k])	i=k+1;
//	else{
//		//���ҵ���һ�������ֵʱ����ǰ������Ѱ������������ֵ 
//        q=p=k;
//        while(score[--p]==check);
//        while(score[++q]==check);
//        flag=1;
//        break;
//	}
//	}
//	if(flag==0) printf("not found");
//	//flag==0��Ҳ��û���ҵ��óɼ� 
//	else 
//	{	
//	for(int j=p+1;j<q;j++)
//	{//����Ƚ����ֵ���ĸ˳�򣬲�����ĸ˳��ǰ������ͨ�������������ƶ� 
//			for(int i=0;i<4&&j<q-1;i++)
//			{
//				if(name[j][i]>name[j+1][i])
//				{
//				printf("enter!\n");
//				char m[20];
//                strcpy(m,name[j]);
//                strcpy(name[j],name[j+1]);
//                strcpy(name[j+1],m);
//				break;
//				}
//				else break;
//			}	
//			//������������ĳɼ������� 
//		printf("%s %d\n",name[j],score[j]);
//	}	
//	}
//	}
	}
	return 0;
}
//void bubble_sort(struct article_information shop)
//{
//	int i,j,t;
//	struct article_information mid[number];
//	for (i=0;i<number-1;i++)
//	{
//	for(j=0;j<number-i-1;j++)
//	{
//		if(shop[j].price<shop[j+1].price)
//		{
//			t=shop[j].price,shop[j].price=shop[j+1].price,shop[j+1].price=t;
//			mid[j].name=shop[j].name,shop[j].name=shop[j+1].name,shop[j+1].name=mid[j].name;
//			mid[j].code=shop[j].code,shop[j].code=shop[j+1].code,shop[j+1].code=mid[j].code;
//			t=shop[j].quality,shop[j].quality=shop[j+1].quality,shop[j+1].quality=t;
//			t=shop[j].prodate,shop[j].prodate=shop[j+1].prodate,shop[j+1].prodate=t;
//		}
////		if(b[j]==b[j+1])	
//		{
//			for(int i=0;i<4;i++)
//			{
//				if(a[j][i]>a[j+1][i])
//				{
//				for(int k=0;k<10;k++)
//				{
//				m[j][k]=a[j][k];
//				a[j][k]=a[j+1][k];
//				a[j+1][k]=m[j][k];	
//				}
//				break;
//				}
//				else if(a[j][i]==a[j+1][i]) continue; 
//				else break;
//			}	
//		}
//	}
//}
//}
