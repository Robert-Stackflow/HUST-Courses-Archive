#include<Stdio.h>
void strnCpy(char t[],char s[],int n){
	int j=0;
	for(int i=0;i<n;i++)
		t[j++]=s[i];
	t[j]='\0';
} 
int main(void)
{
	char t[100];
	char s[100];
	int n;
	printf("�������ַ���s:");
	gets(s);
	printf("����������n:"); 
	scanf("%d",&n);
	strnCpy(t,s,n);
	puts(t);
	return 0;
}
