#include<stdio.h>
//�������� 
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
//���������ǽ�ʱ��������ÿռ任ʱ��ķ���
//������˵�һ���Ӧ�±�������ֵ��Ϊ������ 

//����һ�������Ǹ��´𰸵ķ���
//int main()
//{
//    int a,b;//ѧУѧϰСʱ������ѧϰСʱ
//    int max_time = 0;//��ǰ���ѧϰ��ʱ��
//    int answer = 0;//��
//    for(int i = 0;i < 7;++i) {//�����������ݲ�����
//        scanf("%d %d",&a,&b);//�����i+1���ѧУѧϰСʱ�����ѧϰСʱ
//        if(a + b > max_time && a + b > 8) {//�����ʱ��>8���ҵ�ǰ��ʱ���֮ǰ�ҵ��������ʱ���
//            answer = i + 1;//���´�Ϊ��ǰ����
//            max_time = a + b;//�������ֵ
//        }
//    }
//    printf("%d",answer);//��ӡ��
//    return 0;
//}
