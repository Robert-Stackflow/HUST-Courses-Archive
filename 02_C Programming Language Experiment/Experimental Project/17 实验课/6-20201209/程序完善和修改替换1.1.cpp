# include<stdio.h>
# include<string.h>
#include<stdlib.h>
//#define N 4
/*����������
abfg
chgi
cajp
bklg
*/
void strsort(char*s[],int size)
{//��ʱs[]��ָ�����飬�������tempҲ��ָ�룬�ʿ��Ը�ֵ 
	char *temp;
	int i,j;
	//ð�ݷ����� 
	for(i=0;i<size-1;i++)
	{
		for(j=0;j<size-i-1;j++)
		{
			if(strcmp(s[j],s[j+1])>0)
			{
				//������ַ��������Ӧ���ַ��� 
				temp=s[j];
				s[j]=s[j+1];
				s[j+1]=temp;
			}
		}
	}
}
int main(void)
{
	int i,N;
	char c;
	scanf("%d",&N);
	c=getchar();
	char *s[N],t[50];
	//����ָ������s 
	for(i=0;i<N;i++)
	{
		gets(t);//�����ַ���t 
//		printf("��%d���ַ����ĳ���Ϊ:%d\n",i+1,strlen(t));
		s[i]=(char *)malloc(strlen(t)+1);
		//s�洢����ָ�루������ַ�����ַ�� 
		//mannoc���붯̬�ڴ�
		//��char *����ָ��ǿ��ת��Ϊchar����ָ�롣 
		strcpy(s[i],t);
		//s�洢����ָ�룬*s������洢�����ݣ���ַ��
		//&s[i]�������ַ��s[i]ָ��һ����ַ 
		//s[i]�洢�洢�ĵ�ַ��*s[i]������洢�ĵ�ַ��Ӧ������ 
	}
	strsort(s,N);
	printf("\n");
	for(i=0;i<N;i++)	puts(s[i]);
	//puts����ԭ��Ϊ��const *s)  
	return 0;
 } 
