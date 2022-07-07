#include<stdio.h>
#include<string.h>
#define SIZE 100
int isPalindrome(char arr[],int len);
int main(void)
{
	char arr[SIZE];
	scanf("%s",arr);
	int len=strlen(arr);
	if(isPalindrome(arr,len))
		printf("YES");
	else
	 printf("NO");
	return 0;
} 

int isPalindrome(char arr[],int len)
{
	int count=0;
	for(int i=0;i<len/2;i++)
	{
		if(arr[i]==arr[len-i-1])
		{
			if(count==len/2)
				return 1;
		}
		else		return 0;	
	}
}
