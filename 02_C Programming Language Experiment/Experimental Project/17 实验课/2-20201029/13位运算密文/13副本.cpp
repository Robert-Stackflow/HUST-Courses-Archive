#include<stdio.h>
#include<string.h>
int main()
{
	char a[80];
	printf("请输入字符："); 
	gets(a);
	int k;
	printf("k=");
	scanf("%d",&k);
	for(int i=0;i<=strlen(a);++i){
		if(a[i]>='A'&&a[i]<='Z'||a[i]=='.'||a[i]==','||a[i]==' ')
		{
			if(a[i]<='Z'&&a[i]>='A')
		{
			if(a[i]+k>'Z')
			{
				a[i]=a[i]+k-27;
			}
			else
			{
				a[i]+=(k-1);
			}
		}
		else
		printf("字符有问题"); 
	}
	}
	int m=0;
	while(a[m]!='\0')
		{
			a[m]=a[m]^a[m+1];
			a[m+1]=a[m+1]^a[m];
			a[m]=a[m]^a[m+1];
			m+=2;
		}
	puts(a);
	return 0;
}

