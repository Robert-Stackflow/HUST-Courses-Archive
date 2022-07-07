#include<stdio.h> 
int main(void)
{
	char c;
	int ln,dn,bn;
	ln=bn=dn=0;
	printf("输入一段以Ctrl+z结束的正文\n");
	while((c=getchar())!=EOF)
	{
		if((c>='a'&&c<='z')||(c>='A'&&c<='Z'))	ln++;
		if(c>='0'&&c<='9')	dn++;
		if(c=='\t'||c=='\n'||c==' ')	bn++;
	 } 
		printf("英文字母的个数是%d,数字的个数是%d,空白符的个数是%d",ln,dn,bn);
		return 0;
}
