#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#define MAXLINES 500/*�������*/
#define MAXLEN 100/*������ַ���*/
char * lineptr[MAXLINES];/*�����ַ�ָ������lineptr*/
int readlines(char *[],int);/*�����к�����ԭ������*/
void writelines(char *[],int);/*дһ�к�����ԭ������*/
void sort(void *[],int,int (*)(void *,void *));/*��������ԭ������*/
int numcmp(void *s1,void *s2);/*�����ַ����ȽϺ�����ԭ������*/
int getline(char *,int);/*��һ�к�����ԭ������*/
void swap(void *v[],int i,int j);/*����ָ������Ԫ�صĺ���ԭ������*/
int main(int argc, char* argv[])/*�������в�����main����*/
{	int nlines,numeric = 0;
	if(argc > 1 && strcmp(argv[1],"-n")==0)/*�ж���������ҵ�2��������-n*/
		numeric=1;/*����ֵ�Ƚϱ�־*/
	if((nlines=readlines(lineptr,MAXLINES))>=0){/*������,��������nlines,������>=0*/
/*������������lineptr������ǿ��ת��Ϊ(void **)��numeric��0������ֵ�ȽϺ���numcmp��
��������ַ����ȽϺ���strcmp���������ʽ���������Ҫǿ��ת��Ϊ(int (*)(void *,void *)) */
	sort((void **)lineptr,nlines,(int (*)(void *,void *)) (numeric ? numcmp:strcmp));
	writelines(lineptr,nlines);/*��������ָ������lineptrָ���nlines���ַ���*/
	return 0;
	}
	else {/*��nlines==-1�����������й���*/
		printf("input too big to sort\n");/*�������̫�࣬�޷�����*/
		return 1;
	}
}
void sort(void *v[],int n,int (*comp)(void *,void *))/*��v��Ԫ�ذ���comp��������*/
{	int i,j;/*������β�comp�Ǻ���ָ�룬��ָ������������ֵ��ָ���βΣ���������*/
	for(i=0;i<n-1;i++){/*����ð�ݷ�����*/
		for(j=0;j<n-i-1;j++)
			if((*comp)(v[j],v[j+1])>0)/*��v����������ָ��Ԫ�ذ���comp�Ĺ�����бȽ�*/
				swap(v,j,j+1);/*����v����������ָ��Ԫ�ص�ֵ*/
	}
}
void swap(void *v[],int i,int j)
{	void *t;
	t=v[i],v[i]=v[j],v[j]=t;/*����v��v[i]��v[j]����ָ��Ԫ�ص�ֵ*/
}
int numcmp(void *s1,void *s2)/*�������ַ���������ֵ�Ƚϵĺ���*/
{	double v1,v2;
	v1 = atof((const char *)s1);/*����atof���������ִ�ת��Ϊdouble��������*/
	v2 = atof((const char *)s2);/*Ȼ��ֱ𸳸�v1��v2*/
	return (v1<v2?-1: v1>v2?1:0);/*��v1��v2���бȽϣ�v1С����-1���󷵻�1����ȷ���0*/
}
int readlines(char *lineptr[],int maxlines)/*��������maxlines���ַ����ĺ���*/
{	int len,nlines=0;
	char *p,line[MAXLEN];
	while((len = getline(line,MAXLEN))>0)/*��һ�У��г��ȸ���len*/
		if(nlines>=maxlines || (p=(char *)malloc(len))==NULL)
			return (-1);/*��������л�̬�洢����ʧ�ܣ�����-1*/
		else{/*δ����������Ҷ�̬�洢����len���ֽڳɹ�*/
			line[len-1]='\0';/*β����'\0'�γ��ַ���*/
			strcpy(p,line);/*��line�ַ������е��ַ��������Ѿ�����Ķ�̬�洢��*/
			lineptr[nlines++] = p;/*��ָ��̬�洢����ָ��ֵ����ָ������Ԫ��*/
		}
	return (nlines);/*�����Ѿ����������*/
}
void writelines(char *lineptr[],int nlines)/*���ָ������ָ��Ķ����ַ�������*/
{	while(nlines-- >0)	/*���ж������Ƿ����0��Ȼ��������1*/
		printf("%s\n",*lineptr++);/*���*lineptrָ����ַ�����Ȼ��lineptr��1ָ���¸���*/
}
int getline(char *s,int lim)/*��������lim���ַ���һ�к���*/
{	int c,i=0;/*�������ִ��lim��1���Դ���0�Ҷ���ĵ����ַ���EOF���ҷǻ��з�*/
	while(--lim>0 && (c=getchar())!=EOF && c != '\n')
		s[i++]=c;/*�������ַ���ŵ�s���飬Ȼ���±��1ָ���¸�����λ��*/
	if(c=='\n')/*�������ַ��ǻ��з�*/
		s[i++]='\0';/*β����'\0'�γ��ַ���*/
	return (i);/*�����ַ����ĳ���*/
}