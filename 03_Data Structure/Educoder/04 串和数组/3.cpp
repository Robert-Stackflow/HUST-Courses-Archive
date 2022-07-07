#include "stdio.h"
#include "stdlib.h"
#include "string.h"
typedef struct {
	char *ch;
   int length;
} HString;
void Replace(HString &S,HString T,HString V);
int main()
{
HString S[3];
char buf[100],i,j;
for(i=0;i<3;i++)
{
	fgets(buf,100,stdin);
	S[i].length=strlen(buf)-1;  //-1��ȥ���س�����
	S[i].ch=(char *)malloc(S[i].length);
	for(j=0;j<S[i].length; j++)
		S[i].ch[j]=*(buf+j);
}
Replace(S[0],S[1],S[2]);
printf("S�ĳ��ȣ�%d\n",S[0].length);
for(i=0;i<S[0].length;i++)
	putchar(S[0].ch[i]);
return 1;

}
int SubString(HString* Sub, HString S, int pos, int len) {
    int i;
    if(len == 0) {
        (*Sub).ch=NULL;
        (*Sub).length=0;
        return 1;
    }
    (*Sub).ch=(char*)malloc(len*sizeof(char));
    if(!(*Sub).ch) {
        exit(-2);
    }
    for(i=0;i<len;i++) {
        (*Sub).ch[i]=S.ch[i+pos-1];
    }
    (*Sub).length=len;
    return 1;
}
int Index(HString S, HString T, int pos) {
    int i, s, t;
    HString sub;
    s = S.length;
    t = T.length;
    i = pos;
    while(i + t - 1 <= s) {
        SubString(&sub,S,i,t);
        if(strcmp(sub.ch,T.ch)!=0) {
            ++i;
        }else{
            return i;
        }
    }

    return 0;
}
int StrInsert(HString* S, int pos, HString T) {
    int i;

    if(pos < 1 || pos > (*S).length + 1) {
        return 0;
	}
    // �����¿ռ䣬�Ὣ��Ԫ��һ���ƹ�ȥ
    (*S).ch = (char*) realloc((*S).ch, ((*S).length + T.length) * sizeof(char));
    if(!(*S).ch) {
        exit(-2);
    }

    // ��S���ڳ�λ�ã�Ϊ����T��׼��
    for(i = (*S).length - 1; i >= pos - 1; i--) {
        // �Ӻ���ǰ��������ǰ���Ԫ��Ų������
        (*S).ch[i + T.length] = (*S).ch[i];
    }

    // ����T������S���ڳ���λ����
    for(i = pos - 1; i <= pos + T.length - 2; i++) {
        (*S).ch[i] = T.ch[i - pos + 1];
    }

    // ��������
    (*S).length += T.length;

    return 1;
}
int StrDelete(HString* S, int pos, int len) {
    int i;

    if(pos < 1 || pos + len - 1 > (*S).length || len < 0) {
        return 0;
    }

    // �����ɾ���ĳ���Ϊ0������ǰ����
    if(len == 0) {
        return 1;
    }

    // �Ѻ����Ԫ��Ų��ǰ�棬���ǵ���ɾ����Ԫ��
    for(i = pos + len - 1; i <= (*S).length - 1; i++) {
        (*S).ch[i - len] = (*S).ch[i];
    }

    // ���ȼ���
    (*S).length -= len;

    // ��������Ŀռ䣨������ȼ���Ϊ0������᷵�ؿ�ָ�룩
    (*S).ch = (char*) realloc((*S).ch, (*S).length * sizeof(char));

    return 1;
}
void Replace(HString &S,HString T,HString V)
{
	int i;
    i=Index(S,T,1);
    while(i!=0) {
        StrDelete(&S,i,T.length);
        StrInsert(&S,i,V);
        i+=V.length-1;
        i=Index(S,T,i);
    }
}
