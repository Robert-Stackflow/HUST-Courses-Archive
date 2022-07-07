#include<stdio.h>
#include<string.h>
int n,check[101][101]={0};
//n记录方阵边长，check记录出现的正确单词的位置
int dirx[]={0,1,1, 1, 0,-1,-1,-1};
//搜索时x轴上移动的方向
int diry[]={1,1,0,-1,-1,-1, 0, 1};
//搜索时y轴上移动的方向
char now[10],right[]="yizhong",squre[101][101];
//now记录现在已得到的单词
//right记录正确的待匹配的单词
//squre记录输入的单词方阵
int judge(int x,int y);
//judge函数用来判断是否越界
int judge2(char c);
//优化1：judge2函数用来判断当前位置的字母是否在待匹配单词中，减少循环次数
void display();
//display函数用来输出最终得到的新的单词方阵
void dfs(void);
//dfs函数用来搜索单词并修改check数组
int main(void)
{
	scanf("%d",&n);
	for(int i=0;i<n;i++) scanf("%s",squre[i]);
	//读入数据
	dfs();
	//调用函数搜索
	display();
	//调用函数输出
}
int judge(int x,int y)
{
	if(x>=0&&x<=n&&y>=0&&y<=n) return 1;
	else return 0;
}
int judge2(char c)
{
	for(int i=0;right[i];i++)
		if(c==right[i]) return 1;
	return 0;
}
void dfs()
{
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(squre[i][j]=='y')
			{//如果待匹配单词的首字母'y'出现则开始搜索单词
				for(int k=0;k<8;k++)
				{//循环变量k用来控制搜索的方向
					int I=i,J=j;
					//记录下首字母出现的位置，防止改变变量i和j
					for(int p=0;p<7&&(judge(I+dirx[k],J+diry[k])||judge(I,J))&&judge2(squre[I][J]);p++)
					{//在一个方向上一直移动7次得到一个长度与待匹配单词相等的单词
					//控制条件有移动次数，边界溢出判断，单词与字母含于关系判断来减少语句执行次数
						now[p]=squre[I][J];//读入当前经过的字母
						I+=dirx[k];
						J+=diry[k];//下标继续向该方向移动
					}
					I-=dirx[k];
					J-=diry[k];//下标回溯一个单位，来正确地标记已经查找到的单词
					if (strncmp(now,"yizhong",7)==0)
					{//如果单词匹配则回溯标记check数组
						while(squre[I][J]!='y')
						{//控制何时标记结束
							check[I][J]=1;//标记
							I-=dirx[k];
							J-=diry[k];//回溯
						}
						check[I][J]=1;//标记首字母
					}
					for(int i=0;i<10;i++) now[i]='a';
//					printf("\n");
//					display();
				}
			}
		}
	}
}
void display()
{
//	printf("----------OUTPUT----------\n");
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(check[i][j])printf("%c",squre[i][j]);
			else printf("*");
		}
		printf("\n");
	}
}
