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
	//now��¼��ǰÿ����������ɵĹ�������bf��Ǵ˴ι�����ɺ��ʱ���
	//schedule��¼��ʼ����˳��machine��¼ĳ�����Ѿ���ռ�ݵ�ʱ��Σ�ֵΪ1ʱ��ʾռ��
	scanf("%d%d",&m,&n);
	for(int i=0;i<m*n;i++) scanf("%d",&schedule[i]);
	//��������Ĺ�����˳��
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++)
			scanf("%d",&work[i][j].machine);}
	//����n�������ĸ�������m�����򣩹������û�����
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++)
			scanf("%d",&work[i][j].time);}
	//����n�������ĸ�������m�����򣩹�������ʱ��
	for (int i=0;i<m*n;i++) {
        int current=schedule[i];//��λ��ǰ�����ŵĲ���
        now[current-1]++;//now��¼ÿ����������ɵĹ�����
        int mac=work[current-1][now[current-1]-1].machine,time=work[current-1][now[current-1]-1].time;
        //��¼��ǰ���������ʱ��ͻ�����
        //macָ����ǰ�����ĵ�ǰ�����Ӧ�Ļ�����
		//timeָ����ǰ�����ĵ�ǰ�����Ӧ��ʱ��
//    printf("%d:cur=%d,machine=%d,time=%d\a\n",i,current,mac,time);
    //��ӡ��ǰ����ռ�õĻ�����ռ��ʱ��
        int s=0;
        for (int j=bf[current-1]+1;;j++) {
        	//����j���ϴι�����ɺ��ʱ���ʼ
        	//jָʾ��ǰ��ʱ���α꣬sָʾ��ǰ�������յ���ʱ�䵥λ
            if (machine[mac][j]==0)s++;
        	else s=0;//����յ������������򸳿յ�ʱ��Ϊ0���������д���ν��α�����
            if(s==time)
			{//����յ�ʱ��������㵱ǰ���������������
            for(int k=j-time+1;k<=j;k++)machine[mac][k]=1;
            //���Ѿ������������ʱ��α��Ϊ1���û����ĸö�ʱ�����ѱ�ռ��
//    printf("%d:%d~%d�ѱ�ռ��\n",mac,j-time+1,j);
    //��ӡ�ѱ�ռ�ݵ�ʱ����
            if (j>res) res=j;//�����ǰ�ܹ�����ʱ��ҪС�ڴ���ǰ������������ʱ�䣬��ʱ�����
            bf[current-1]=j;//��¼�˴ν����깤����ʱ���߱��
            break;
            }
        }
	system("pause");
	//�۲쵱ǰ���е����ݽ��
    }
    printf("%d\a\n",res);
//    system("pause");
}
