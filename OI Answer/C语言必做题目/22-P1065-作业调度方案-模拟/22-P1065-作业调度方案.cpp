#include<stdio.h>
#include<stdlib.h>
#define N 10000
struct work{
	int machine;
	int time;
}work[25][25];
int main(void)
{
	int m,n,res=0;
	int now[25]={0},bf[25]={0},schedule[405],machine[25][N]={0};
	//now记录当前每个工件已完成的工序数，bf标记此次工序完成后的时间点
	//schedule记录初始安排顺序，machine记录某机器已经被占据的时间段，值为1时表示占用
	scanf("%d%d",&m,&n);
	for(int i=0;i<m*n;i++) scanf("%d",&schedule[i]);
	//读入给定的工序安排顺序
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++)
			scanf("%d",&work[i][j].machine);}
	//读入n个工件的各个（共m个工序）工序所用机器号
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++)
			scanf("%d",&work[i][j].time);}
	//读入n个工件的各个（共m个工序）工序所用时间
	for (int i=0;i<m*n;i++) {
        int current=schedule[i];//定位当前所安排的操作
        now[current-1]++;//now记录每个工件所完成的工序数
        int mac=work[current-1][now[current-1]-1].machine,time=work[current-1][now[current-1]-1].time;
        //记录当前工件所需的时间和机器号
        //mac指代当前工件的当前工序对应的机器号
		//time指代当前工件的当前工序对应的时间
//    printf("%d:cur=%d,machine=%d,time=%d\a\n",i,current,mac,time);
    //打印当前工件占用的机器与占用时长
        int s=0;
        for (int j=bf[current-1]+1;;j++) {
        	//变量j从上次工序完成后的时间后开始
        	//j指示当前的时间游标，s指示当前的连续空当的时间单位
            if (machine[mac][j]==0)s++;
        	else s=0;//如果空当不满足条件则赋空当时间为0，跳过下列代码段将游标右移
            if(s==time)
			{//如果空当时间可以满足当前工件的需求则进入
            for(int k=j-time+1;k<=j;k++)machine[mac][k]=1;
            //将已经用来处理工序的时间段标记为1，该机器的该段时间线已被占据
//    printf("%d:%d~%d已被占据\n",mac,j-time+1,j);
    //打印已被占据的时间线
            if (j>res) res=j;//如果先前总共所需时间要小于处理当前工件后所用总时间，则将时间更新
            bf[current-1]=j;//记录此次进行完工序后的时间线标记
            break;
            }
        }
	system("pause");
	//观察当前运行的数据结果
    }
    printf("%d\a\n",res);
//    system("pause");
}
