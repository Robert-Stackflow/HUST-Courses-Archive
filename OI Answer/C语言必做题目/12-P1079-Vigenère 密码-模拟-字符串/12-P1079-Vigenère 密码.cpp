#include<stdio.h>
#include<string.h>
//�ҵ������Ĺ��ɱ�ӭ�ж���
//����Ҫע����չ��Կ�ַ�����ʡȴ��ѭ��ʹ����Կ�Ĺ��� 
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
//��������һ�ֱȽϼ������(C++�� 
//˼·��һ������ASCII���С֪ʶ��
//��ĸ'A'��ASCII����41H��0100 0001B������ĸ'a'��ASCII����61H��0110 0001B����
//��ĸ'A'��'a'�Ķ����ƺ�5λ����ͬ�ģ����������Ǵ�д��ĸ����Сд��ĸx��
//x&31��1 1111B����ֵ����x����ĸ�����˳��
//��ʼ��⣺
//�����Ŀ�ľ����������ȥ��λ��������Կk������ַ�'C'����ľ�����������2λ�õ����ģ���������֪���ģ�
//'C'����ľ�����ǰ��2λ������'Y'�͵õ���'W'��
//����λ���б߽�ģ���������۹���ͷ����Ҫ�ٻ�����A֮�����Z�ˡ�
//������Ҫ�ж�һ�����ĵĺʹ�λ֮��Ĵ�С�������λ����Ҫ��26. 
//�������£�
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
