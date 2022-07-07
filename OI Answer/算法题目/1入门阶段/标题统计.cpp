#include<stdio.h>
#include<string.h>
int main(void)
{
    char name[6];
    int ans=0;
    gets(name);
    for(int i=0;i<strlen(name);i++) if((name[i]>='A'&&name[i]<='Z')||(name[i]>='a'&&name[i]<='z')||(name[i]>='0'&&name[i]<='9')) ans++;
	printf("%d",ans);
	return 0;
}
