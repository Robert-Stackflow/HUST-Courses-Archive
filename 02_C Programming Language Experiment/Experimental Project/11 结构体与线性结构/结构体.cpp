#include<stdio.h>
#define N 3
//�ṹ��Ķ����븳ֵ����ʼ��
//�洢�ռ���䣬��ռ�ֽ������ı����ŵ���ǰ�������
//����ָ�벢��ָ��Խṹ����з���(->��ͷ�����) 
//���ʽṹ������ַ�ʽ
//���庯���Խṹ����в�����������ָ��ʹ�ü�ͷ�ٴγ��Բ�����
//����typedef����ṹ��������ϵͳ���������ͺ��Լ�������������Ͷ��ɣ�
//����typedef int integer 
//������typedef struct person{...}myperson;
//typedef struct person myperson; 
//����Ҳ���Ը�ָ��ṹ������������͵�ָ��ȡ����
//�Ѷ����ͬ�ṹ�����͵�Ԫ�ش���һ�������У��ṹ���飩,������ָ�������в���
//Ƕ�׽ṹ��Ķ�����ʹ�ã���һ���˵ĳ������ڵ���/��/��/ʱ/��/��)
//�������ͥסַ��ʡ/��/��/��/��/���
//����Ʒ����������Ʒʶ���뼰�۸����������Ҫ��ʵ�ֲ˵�����ҹ��ܲ������ú�����װ����
struct person{
	char name[18];
	int age;
	double height;	
};//����һ���ṹ��ͬʱ��ʼ�� 
typedef struct result{
	char name[18];
	int programming;
	double math;
}result;//���ṹ����������� 
struct stu_study{
	char num[6];
	char name[18];
	char sex;
	int English;
	int Math,Physics,C_programming;
}XRD={"15533","Xu Ruida",'m',81,92,76,85};
//����ṹ�����XRDͬʱ������г�ʼ��
struct date{
	int year;
	int month;
	int day;
	int hour;
}; //�������ڽṹ�� 
struct address{
	char province[10];
	char city[10];
	char county[10];
	char villege[10];
	int  group; 
};//�����ַ�ṹ�� 
struct information
{
	char name[18];
	struct date birthday;
	struct address house;
};//Ƕ�׽ṹ�����ѧ�����������������ڣ���ͥסַ 
int main(void)
{
	printf("stu_study���͵Ľṹ�����XRD�ĸ����������£�%s\t%s\t%c\t%d\t%d\t%d\t%d\n",XRD.num,XRD.name,XRD.sex,XRD.English,XRD.Math,XRD.Physics,XRD.C_programming);
	struct person a,*pa=&a;
	printf("�������������������䣬��ߣ�");
	scanf("%s%d%lf",&a.name,&a.age,&a.height); 
	printf("person���͵Ľṹ��a����������������߷ֱ����£�%s\t%d\t%.1lf\n",a.name,a.age,a.height);
	result b={"hust",89,92},*pb=&b;
	printf("result���͵Ľṹ��b����������̳ɼ�����ѧ�ɼ��ֱ����£�%s\t%d\t%.1lf",pb->name,pb->programming,pb->math);
	struct person grade[N];//����ṹ�������ڴ洢����N���˵���Ϣ 
	for(int i=0;i<N;i++)
		scanf("%s%d%lf",&grade[i].name,&grade[i].age,&grade[i].height);
	for(int i=0;i<N;i++)
		printf("��%d���˵���ϢΪ%s\t%d\t%lf\n",i+1,grade[i].name,grade[i].age,grade[i].height);
}
