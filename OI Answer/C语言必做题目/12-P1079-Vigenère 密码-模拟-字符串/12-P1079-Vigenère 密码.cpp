#include<stdio.h>
#include<string.h>
//找到密码表的规律便迎刃而解
//其中要注意扩展密钥字符串，省却了循环使用密钥的过程 
int main(void)
{
	char key[1010],in[1010],out[1010];
	scanf("%s%s",key,in);
	int len=strlen(key);
	if(strlen(in)>strlen(key)){
	for(int i=strlen(key);i<strlen(in);i++)	key[i]=key[i-len];
	}
	for(int i=0;in[i]!='\0';i++)
	{
		int change=((key[i]<='z'&&key[i]>='a')?key[i]-'a':key[i]-'A');
		out[i]=in[i]-change;
		if(in[i]<='z'&&in[i]>='a')
		{if(out[i]<'a') out[i]+=26;}
		if(in[i]<='Z'&&in[i]>='A')
		{if(out[i]<'A') out[i]+=26;}	
	}
	for(int i=0;i<strlen(in);i++)
	printf("%c",out[i]);
}
//下面是另一种比较简洁的题解(C++） 
//思路是一个关于ASCII码的小知识：
//字母'A'的ASCII码是41H（0100 0001B），字母'a'的ASCII码是61H（0110 0001B），
//字母'A'与'a'的二进制后5位是相同的，所以无论是大写字母还是小写字母x，
//x&31（1 1111B）的值就是x在字母表里的顺序。
//开始题解：
//本题的目的就是问你如何去篡位，例如秘钥k里面的字符'C'代表的就是明文向后篡2位得到密文，反过来已知密文，
//'C'代表的就是向前篡2位，这样'Y'就得到了'W'。
//而篡位是有边界的，就是如果篡过了头，需要再回来，A之后就是Z了。
//所以需要判断一下密文的和篡位之间的大小，如果篡位大，需要补26. 
//代码如下：
//int main() {
//	string k,c;
//	cin>>k>>c;
//	for (int i=0;i<c.length();i++) {
//		int t=(k[i%k.length()]&31)-1;
//		c[i]=(c[i]&31)-t>0?c[i]-t:c[i]-t+26;
//	}
//	cout<<c<<endl;
//	return 0;
//} 
