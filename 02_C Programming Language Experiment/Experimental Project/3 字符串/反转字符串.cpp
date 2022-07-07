#include<stdio.h> 
int strlen(char s[]){
	int i;
	i=0;
	while(s[i]!='\0')
	++i;
	return i;
} 
int main(void)
{ 
	char s[100],mid;
	printf("Input a string:");
	scanf("%s",s);
	int i=0,j;
	j=strlen(s)-1;
	while(i<j)
	{
		mid=s[i];
		s[i]=s[j];
		s[j]=mid;
		i++;
		j--; 
	}
	printf("%s",s);
	return 0;
}
