#include<stdio.h> 
//�������� 
void codel(char t[],char mid[],int n);
void strcate(char t[],char s[]);
void strnins(char t[],char s[],int n);

int main(void)
{
	char t[100],s[100];
	int n;
	scanf("%s%s%d",t,s,&n);
	strnins(t,s,n);
	printf("%s",t);
}

void codel(char t[],char mid[],int n)
{//������t�Ե�n���ַ�����ַ����Ƶ��м������У���������t�ĺ�벿��ɾ��
	int i=0,k=n;
	for(;t[k]!='\0';i++,k++)
		mid[i]=t[k];
	mid[i]='\0';
	t[n]='\0';
}

void strcate(char t[],char s[])
{//��һ���ַ���ƴ�ӵ���һ���ַ�����
	int i=0,j=0,k=-1;
	while(t[i++]);
	i--;
	while((t[i++]=s[j++])!='\0'); 
}

void strnins(char t[],char s[],int n)
{//������������������ʵ�ֲ����ַ������ܣ�
	char mid[100];
	codel(t,mid,n);
	strcate(t,s);
	strcate(t,mid);
}
