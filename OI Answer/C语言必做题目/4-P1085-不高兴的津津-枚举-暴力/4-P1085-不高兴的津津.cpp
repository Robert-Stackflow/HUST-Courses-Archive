#include<stdio.h>
//输入样例 
//5 6
//2 4
//3 1
//0 4
//0 8
//7 4
//3 5
int main(void)
{
	int time[7][3],rank[20]={0};
	for(int i=0;i<7;i++)
	scanf("%d%d",&time[i][0],&time[i][1]);
	for(int i=6;i>=0;i--)
	rank[time[i][0]+time[i][1]]=i+1;
	for(int i=19;i<20;i--)
	if(rank[i]!=0) {printf("%d",rank[i]);break;}
}
//该种做法是将时间输入后，用空间换时间的方法
//将最不高兴的一天对应下标的数组的值赋为星期数 

//另外一种做法是更新答案的方法
//int main()
//{
//    int a,b;//学校学习小时，课外学习小时
//    int max_time = 0;//当前最大学习总时间
//    int answer = 0;//答案
//    for(int i = 0;i < 7;++i) {//读入七组数据并处理
//        scanf("%d %d",&a,&b);//读入第i+1天的学校学习小时与课外学习小时
//        if(a + b > max_time && a + b > 8) {//如果总时间>8并且当前总时间比之前找到的最大总时间大
//            answer = i + 1;//更新答案为当前星期
//            max_time = a + b;//更新最大值
//        }
//    }
//    printf("%d",answer);//打印答案
//    return 0;
//}
