#include<stdio.h> 
int main(void)
{
	char c;
	int ln,dn,bn;
	ln=bn=dn=0;
	printf("����һ����Ctrl+z����������\n");
	while((c=getchar())!=EOF)
	{
		if((c>='a'&&c<='z')||(c>='A'&&c<='Z'))	ln++;
		if(c>='0'&&c<='9')	dn++;
		if(c=='\t'||c=='\n'||c==' ')	bn++;
	 } 
		printf("Ӣ����ĸ�ĸ�����%d,���ֵĸ�����%d,�հ׷��ĸ�����%d",ln,dn,bn);
		return 0;
}
