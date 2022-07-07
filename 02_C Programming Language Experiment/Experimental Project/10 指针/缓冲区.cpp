#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
int main()
{
	//缓冲区样例，该代码是在一串同时含有字符,数字，标点，空格的字符串中输出所有数字
	char s[100],temp[100]/*temp为缓冲区*/;
	int i,j,k;
	gets(s);
	for(i = 0;s[i] != '\0';i++)
	{
		if(isdigit(s[i]))//如果是数字，则存入缓冲区 
			temp[j++] = s[i];
		else 
		{
			if(j > 0)
			{//如果不是数字且缓冲区中存在数字，则输出并且将缓冲区归零 
				temp[j] = '\0';
				puts(temp);
				j = 0;
			}else	continue;//如果不是数组且缓冲区中不存在数组，则继续进行 
		}
	}
	
	if(j)//防止结尾存在数字	
	{
		temp[j] = '\0';
		puts(temp);
	}
}
