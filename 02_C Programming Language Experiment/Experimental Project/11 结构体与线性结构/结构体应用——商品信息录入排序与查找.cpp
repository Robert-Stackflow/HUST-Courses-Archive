#include<stdio.h> 
#include<string.h>
//实现录入商品信息，输出商品信息，按价格或商品码排序后进行输出，可查询商品码或者价格，
//排查生产日期在某个范围内的商品，当价格一样时按商品码或者名称顺序输出，
//菜单选项等多个功能，封装函数等功能，预计代码行200行 
/*测试样例：
bread ISBN2345678 6 2 2020 12 13
rice  ISBN1234566 25 3 2020 12 14
*/  
struct date{
	int year;
	int month;
	int day;
}; //定义日期结构体
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
	printf("商品名称\t商品码\t\t商品价格\t商品保质期\t商品出厂日期\n");
    for(int i=0;i<number;i++)
    	printf("%s\t\t%s\t$%d\t\t%dmonths\t\t%d/%d/%d\n",shop[i].name,shop[i].code,shop[i].price,shop[i].quality,shop[i].prodate.year,shop[i].prodate.month,shop[i].prodate.day);
	}
//	if(flag==4)
//	{
//	int check;
//	scanf("%d",&check);
//	int i=0,j=number-1,flag=0,k,result[10],p,q;
//	while(i<=j)
//	{//二分查找 
//	k=(i+j)/2;
//	if(check>score[k])	j=k-1;
//	else if(check<score[k])	i=k+1;
//	else{
//		//当找到第一个满足的值时，向前向后继续寻找满足条件的值 
//        q=p=k;
//        while(score[--p]==check);
//        while(score[++q]==check);
//        flag=1;
//        break;
//	}
//	}
//	if(flag==0) printf("not found");
//	//flag==0，也即没有找到该成绩 
//	else 
//	{	
//	for(int j=p+1;j<q;j++)
//	{//下面比较名字的字母顺序，并将字母顺序靠前的姓名通过交换数组来移动 
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
//			//输出符合条件的成绩和姓名 
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
