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
	S[i].length=strlen(buf)-1;  //-1是去掉回车符号
	S[i].ch=(char *)malloc(S[i].length);
	for(j=0;j<S[i].length; j++)
		S[i].ch[j]=*(buf+j);
}
Replace(S[0],S[1],S[2]);
printf("S的长度：%d\n",S[0].length);
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
    // 分配新空间，会将旧元素一起复制过去
    (*S).ch = (char*) realloc((*S).ch, ((*S).length + T.length) * sizeof(char));
    if(!(*S).ch) {
        exit(-2);
    }

    // 在S中腾出位置，为插入T做准备
    for(i = (*S).length - 1; i >= pos - 1; i--) {
        // 从后向前遍历，将前面的元素挪到后面
        (*S).ch[i + T.length] = (*S).ch[i];
    }

    // 将串T插入在S中腾出的位置上
    for(i = pos - 1; i <= pos + T.length - 2; i++) {
        (*S).ch[i] = T.ch[i - pos + 1];
    }

    // 长度增加
    (*S).length += T.length;

    return 1;
}
int StrDelete(HString* S, int pos, int len) {
    int i;

    if(pos < 1 || pos + len - 1 > (*S).length || len < 0) {
        return 0;
    }

    // 如果待删除的长度为0，则提前返回
    if(len == 0) {
        return 1;
    }

    // 把后面的元素挪到前面，覆盖掉被删除的元素
    for(i = pos + len - 1; i <= (*S).length - 1; i++) {
        (*S).ch[i - len] = (*S).ch[i];
    }

    // 长度减少
    (*S).length -= len;

    // 缩减分配的空间（如果长度减少为0，这里会返回空指针）
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
