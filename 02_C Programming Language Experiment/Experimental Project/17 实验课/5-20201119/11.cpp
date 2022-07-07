#include<stdio.h> 
/*1 0 0 0 0 0 0 0 0 0
1 0 1 1 0 1 1 1 1 0
1 1 1 0 0 1 1 0 1 0
1 0 0 1 1 1 0 0 1 0
1 1 1 1 0 1 1 1 1 0
0 0 0 0 0 0 0 0 1 1*/
#define ph1 x+moveX[i]>=0
#define ph2 x+moveX[i]<position_x
#define ph3 y+moveY[i]>=0
#define ph4 y+moveY[i]<position_y
#define ph5 road[x+moveX[i]][y+moveY[i]]==0
#define ph6 map[x+moveX[i]][y+moveY[i]]==1
#define ph7 road[x+moveX[i]][y+moveY[i]]=1	
#define ph8 search(x+moveX[i],y+moveY[i])
#define ph9 road[x+moveX[i]][y+moveY[i]]=0
//宏定义运算表达式 
int map[20][20]={};
int road[20][20]={};
void search(int,int);
int moveX[4]={1,0,0,-1};
int moveY[4]={0,1,-1,0};
//定义在x和y方向的移动动作，即二者结合可以进行四个方向的移动，从而可以搜寻四个方向的路径 
int position_x,position_y,num=0;
//定义当前的位置和路径序号 
int main(){
	scanf("%d %d",&position_x,&position_y);
	int i,j;
	for(i=0;i<position_x;i++){
		for(j=0;j<position_y;j++)
			scanf("%d",&map[i][j]);
	}//将迷宫图存入数组中 
	search(0,0);//调用迷宫进行查找路径 
	return 0;
}
void search(int x,int y){
	int i,j;
	if(x==position_x-1&&y==position_y-1){
		//当已经查找到迷宫右下角时，输出已经查找到的路径 
		num++;//标记已经找到的路径序号
		printf("\n--------------------------\n"); 
		printf("%d\n",num);
		for(i=0;i<position_x;i++){
			for(j=0;j<position_y;j++){
				//输出已经存储在road中的路径 
				printf("%d",road[i][j]);
					if(j<position_y-1) printf(" ");
			}
			printf("\n");	
		} 
		printf("\n--------------------------\n");
		return;//输出完成后进行下一次查找路径 
	}
	else{
		road[0][0]=1;
		for(i=0;i<4;i++){
			if(ph1&&ph2&&ph3&&ph4&&ph5&&ph6){
				//当迷宫地图上的下一步是1，即可以走并满足不与已找到的路径重复时时继续执行 
				ph7;//标记自己已经走过的迷宫格为1 
				ph8;//递归进行下一步查找 
				ph9; 
			}
		}
	}
}

