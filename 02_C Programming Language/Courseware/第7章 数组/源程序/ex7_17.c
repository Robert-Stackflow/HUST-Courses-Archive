#include "stdio.h"
void delete_c(char s[],char c);
int main(void)
{
	char s[]="yvovuv vavrvev svtvuvdvevnvtvsv.";
	delete_c(s,'v');
	printf("%s\n",s);
	return 0;
}
void delete_c(char s[],char c)
{	int j=0,k=0;
	while(s[j]!= '\0'){/*对s串中的每个字符*/
		if(s[j]!=c) /*如果不是要删除字符*/
			s[k++]=s[j];/*复制非删字符*/
		j++;/*能够跳过要删除字符*/
	}
	s[k]= '\0';/*构造新串*/
}
