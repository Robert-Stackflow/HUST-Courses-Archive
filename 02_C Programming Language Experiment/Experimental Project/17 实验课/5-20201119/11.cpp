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
//�궨��������ʽ 
int map[20][20]={};
int road[20][20]={};
void search(int,int);
int moveX[4]={1,0,0,-1};
int moveY[4]={0,1,-1,0};
//������x��y������ƶ������������߽�Ͽ��Խ����ĸ�������ƶ����Ӷ�������Ѱ�ĸ������·�� 
int position_x,position_y,num=0;
//���嵱ǰ��λ�ú�·����� 
int main(){
	scanf("%d %d",&position_x,&position_y);
	int i,j;
	for(i=0;i<position_x;i++){
		for(j=0;j<position_y;j++)
			scanf("%d",&map[i][j]);
	}//���Թ�ͼ���������� 
	search(0,0);//�����Թ����в���·�� 
	return 0;
}
void search(int x,int y){
	int i,j;
	if(x==position_x-1&&y==position_y-1){
		//���Ѿ����ҵ��Թ����½�ʱ������Ѿ����ҵ���·�� 
		num++;//����Ѿ��ҵ���·�����
		printf("\n--------------------------\n"); 
		printf("%d\n",num);
		for(i=0;i<position_x;i++){
			for(j=0;j<position_y;j++){
				//����Ѿ��洢��road�е�·�� 
				printf("%d",road[i][j]);
					if(j<position_y-1) printf(" ");
			}
			printf("\n");	
		} 
		printf("\n--------------------------\n");
		return;//�����ɺ������һ�β���·�� 
	}
	else{
		road[0][0]=1;
		for(i=0;i<4;i++){
			if(ph1&&ph2&&ph3&&ph4&&ph5&&ph6){
				//���Թ���ͼ�ϵ���һ����1���������߲����㲻�����ҵ���·���ظ�ʱʱ����ִ�� 
				ph7;//����Լ��Ѿ��߹����Թ���Ϊ1 
				ph8;//�ݹ������һ������ 
				ph9; 
			}
		}
	}
}

