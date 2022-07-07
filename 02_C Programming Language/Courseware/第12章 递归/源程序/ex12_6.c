/************************************************************************************
简要描述：回溯法解0-1背包问题。
*************************************************************************************/
#include<stdio.h>

#define SIZE 100      /* 最多物品数   */

void BackTrack(int t,int cw,int cv);
void printResult(void);
int constrain(int t);

int c;       /* 背包容量     */
int n;       /* 实际物品数   */
int bestv=0;   /* 最优解的总价值   */
int bestx[SIZE];  /* 存放最优解   */
int x[SIZE];      /* 存放当前解       */
struct {
	int w;     /* 重量     */ 
	int v;     /* 价值     */
} a[SIZE];     /* 存放物品的数组  */

int main(void) 
{
	int i;
	printf("请输入物品个数： "); 
    scanf("%d",&n); 
	printf("请输入背包容量： "); 
	scanf("%d",&c); 
    printf("请输入%d个物品的重量：\n",n); 
    for(i=0;i<n;i++) 
		scanf("%d",&a[i].w); 
    printf("请输入%d个物品的价值：\n",n); 
    for(i=0;i<n;i++) 
		scanf("%d",&a[i].v); 
    BackTrack(0,0,0);  
	printResult();
	printf("\n");
	return 0;
}

/************************************************************************************
函数名称：backtrack
函数功能：0-1背包问题的回溯算法。
          考虑第t个物品。 
函数参数：t表示待决策的物品。
          cw表示当前重量
		  cv表示当前价值
函数返回值：无。
************************************************************************************/	 
void BackTrack(int t,int cw,int cv)  
{  
	int i;
	if(t >= n) /* 找到一个叶子节点 */
	{
		if(cv > bestv)  /* 找到一个更优解，保存它 */
		{
			bestv = cv;   
            for(i = 0; i < n; i++)
				bestx[i] = x[i];
		}   
        return;
	}
	/* 如满足约束条件，则搜索左子树(即选取第t个物品) */
	if(a[t].w<=c-cw)   
	{
		x[t]=1;
		BackTrack(t+1,cw+a[t].w,cv+a[t].v);
	}
    /* 搜索右子树(即不选取第t个物品) */	
    x[t]=0; 
    BackTrack(t+1,cw,cv); 
} 

/************************************************************************************
函数名称：printResult
函数功能：输出最优解。 
函数参数：  无。
函数返回值：无。
************************************************************************************/	 
void printResult()
{   
    int i;   

    printf("最优解为: ");   
    for(i = 0; i < n; i++)
    {    
             printf("%d ",bestx[i]);   
    }   
    printf("\n");   
} 