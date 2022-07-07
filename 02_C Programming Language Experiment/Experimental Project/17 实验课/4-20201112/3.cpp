#include<stdio.h> 
int main(void)
{
	int s[1000];
	int day,i=0,point=0,j=2;
	scanf("%d",&day);
	while(i<=day-1){
		scanf("%d",&s[i]);
		++i;
	}	
	while (j<=(day-1)&&s[j+1]!='\0'){
		if((s[j-1]>s[j-2]&&s[j]>s[j-1]&&s[j]>s[j+1])||(s[j-1]<s[j-2]&&s[j]<s[j-1]&&s[j]<s[j+1]))
			++point;
		++j;
	}
	printf("%d",point);
	return 0;	
}
