#include<stdio.h>
#include<string.h>
//样例输入：hust is my home!2019！
//样例输入：aaa bbb ccc ddd !!! 11223344 
//样例输入：C is a general-purpose, high-level language that was originally developed by Dennis M. Ritchie to develop the UNIX operating system at Bell Labs. C was originally first implemented on the DEC PDP-11 computer in 1972. 
int main(void)
{
	char str[1000];
	char all[100]={0};
	int num[127]={0};
	int count=1,flag=0,othercount=0,j=0,sum=0,m=0;
	while(scanf("%c",&str[m]),str[m]!='\n')
		m++;
	str[m]='\0'; 
	char check;
	for(int i=0;i<strlen(str);i++)
	{	
		count=1;
		check=str[i];
		if((check<='Z'&&check>='A')||(check<='z'&&check>='a')||(check<=57&&check>=48))
			{
				if(check<='z'&&check>='a')
				    {
					flag=check-32;
					check=check-32;
					all[flag]=check;
					}
				else
				{
					flag=check;
					all[flag]=check;
				}
				for(int j=i+1;j<strlen(str);j++)
					{
						if(check==str[j]||check==str[j]-32)
						{
							count++;
							str[j]=' ';
						}
					}
				num[flag]=count;
				--count;
				sum+=count;
			}
		else
			othercount++;
}
	for(int k=0;k<127;k++)
	{
		if(num[k]!=0)
		printf("%c:%d\n",all[k],num[k]);
	}
	printf("others:%d",othercount-sum);
	return 0;
} 
