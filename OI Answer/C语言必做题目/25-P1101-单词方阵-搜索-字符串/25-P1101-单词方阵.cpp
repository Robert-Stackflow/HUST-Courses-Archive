#include<stdio.h>
#include<string.h>
int n,check[101][101]={0};
//n��¼����߳���check��¼���ֵ���ȷ���ʵ�λ��
int dirx[]={0,1,1, 1, 0,-1,-1,-1};
//����ʱx�����ƶ��ķ���
int diry[]={1,1,0,-1,-1,-1, 0, 1};
//����ʱy�����ƶ��ķ���
char now[10],right[]="yizhong",squre[101][101];
//now��¼�����ѵõ��ĵ���
//right��¼��ȷ�Ĵ�ƥ��ĵ���
//squre��¼����ĵ��ʷ���
int judge(int x,int y);
//judge���������ж��Ƿ�Խ��
int judge2(char c);
//�Ż�1��judge2���������жϵ�ǰλ�õ���ĸ�Ƿ��ڴ�ƥ�䵥���У�����ѭ������
void display();
//display��������������յõ����µĵ��ʷ���
void dfs(void);
//dfs���������������ʲ��޸�check����
int main(void)
{
	scanf("%d",&n);
	for(int i=0;i<n;i++) scanf("%s",squre[i]);
	//��������
	dfs();
	//���ú�������
	display();
	//���ú������
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
			{//�����ƥ�䵥�ʵ�����ĸ'y'������ʼ��������
				for(int k=0;k<8;k++)
				{//ѭ������k�������������ķ���
					int I=i,J=j;
					//��¼������ĸ���ֵ�λ�ã���ֹ�ı����i��j
					for(int p=0;p<7&&(judge(I+dirx[k],J+diry[k])||judge(I,J))&&judge2(squre[I][J]);p++)
					{//��һ��������һֱ�ƶ�7�εõ�һ���������ƥ�䵥����ȵĵ���
					//�����������ƶ��������߽�����жϣ���������ĸ���ڹ�ϵ�ж����������ִ�д���
						now[p]=squre[I][J];//���뵱ǰ��������ĸ
						I+=dirx[k];
						J+=diry[k];//�±������÷����ƶ�
					}
					I-=dirx[k];
					J-=diry[k];//�±����һ����λ������ȷ�ر���Ѿ����ҵ��ĵ���
					if (strncmp(now,"yizhong",7)==0)
					{//�������ƥ������ݱ��check����
						while(squre[I][J]!='y')
						{//���ƺ�ʱ��ǽ���
							check[I][J]=1;//���
							I-=dirx[k];
							J-=diry[k];//����
						}
						check[I][J]=1;//�������ĸ
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
