#include<stdio.h>
int main(void){
//�����ָ��
	printf("---�����ָ��---\n\n");
	int nums[]={1,2,3};
	int *p1=nums;
	//��ʱnums==p1==&nums==&nums[0] 
	//���������Ǹ�����ĵ�ַ����ʱnums[]��дΪp1[]
	//���������
	printf("%d\t%d\t%d\n\n",p1[0],p1[1],p1[2]); 
//ָ������Ҫ�ͱ������Ͷ�Ӧ 
	/*int intvalue=1230;
	char charvalue='1';
	int *pint;
	//ע���ʱ�ĸ�ֵ�����ǲ��Ϸ��ģ��ᱨ�� 
	//*pint=&charvalue;
	char *pchar;
	//*pchar=&intvalue;
	printf("%d",*pint);
	printf("%d",*pchar);*/
//����ָ��
	printf("---����ָ��---\n\n");
	int num=10;	
	int *nump=&num;
	int **numpp=&nump;
	int ***numppp=&numpp;
	printf("%d\t%d\t%d\n\n",*nump,**numpp,***numppp);
//ָ����ƶ�
	printf("---ָ����ƶ�---\n\n");
	int nums1[]={1,2,3};
	int *p2=nums1;
	printf("nums1[i]:\t");
	for(int i=0;i<3;i++)
		printf("%d ",nums1[i]); 
	printf("\n");
	printf("p2[i]:\t\t");
	for(int i=0;i<3;i++)
		printf("%d ",p2[i]); 
	printf("\n");
	printf("*(p2+i):\t");
	for(int i=0;i<3;i++)
		printf("%d ",*(p2+i));
	printf("\n");
	printf("*(nums1+i):\t");
	for(int i=0;i<3;i++)
		printf("%d ",*(nums1+i));
	printf("\n\n");
//ָ����ַ���
	printf("---ָ����ַ���---\n\n");
	char*p="cs";
	printf("%s\n",p);
	printf("%c%c\n\n",p[0],p[1]);
	//p[1]='d';
	//��ָ��洢�ַ������洢�ڳ�����̬�����������޸��ַ�����
	//������洢�ַ�������洢��ջ�У������޸��ַ�������ִ�����ᱻ�ͷš�
	//�����ͬ��ֵ��Ӧһ����ַ���Ҳ��ᱻ�ͷš�
	//printf("%s",p);
}
