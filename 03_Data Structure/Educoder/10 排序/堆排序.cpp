#include <stdio.h>
#include <stdlib.h>
#define MAX 15
//������¼�Ľṹ��
typedef struct {
    int key;
}SqNote;
//��¼��Ľṹ��
typedef struct {
    SqNote r[MAX];
    int length;
}SqList;
//���� r[s]Ϊ�������������ɶѣ�����ÿ��������ֵ�����亢�ӽ���ֵ��
void HeapAdjust(SqList * H,int s,int m){
    SqNote rc=H->r[s];//�ȶԲ���λ���ϵĽ�����ݽ��б��棬���ú����ƶ�Ԫ�ض�ʧ��
    //���ڵ� s ����㣬ɸѡһֱ��Ҷ�ӽ�����
    for (int j=2*s; j<=m; j*=2) {
        //�ҵ�ֵ���ĺ��ӽ��
        if (j+1<m && (H->r[j].key<H->r[j+1].key)) {
            j++;
        }
        //�����ǰ�������ĺ��ӽ���ֵ��������Ҫ�Դ˽�����ɸѡ��ֱ���Թ�
        if (!(rc.key<H->r[j].key)) {
            break;
        }
        //�����ǰ����ֵ�Ⱥ��ӽ��������ֵС��������ֵ�����ý�㣬���� rc ��¼�Ÿý���ֵ�����Ըý���ֵ���ᶪʧ
        H->r[s]=H->r[j];
        s=j;//s�൱��ָ������ã�ָ���亢�ӽ�㣬��������ɸѡ
    }
    H->r[s]=rc;//�����轫rc��ֵ��ӵ���ȷ��λ��
}
//����������¼��λ��
void swap(SqNote *a,SqNote *b){
    int key=a->key;
    a->key=b->key;
    b->key=key;
}
void HeapSort(SqList *H){
    //�����ѵĹ���
    for (int i=H->length/2; i>0; i--) {
        //�����к��ӽ��ĸ�������ɸѡ
        HeapAdjust(H, i, H->length);
    }
    for (int i=1; i<=10; i++) {
        printf("%d ",H->r[i].key);
    }
    printf("\n");
    //ͨ�����ϵ�ɸѡ�����ֵ��ͬʱ���ϵؽ���ɸѡʣ��Ԫ��
    for (int i=H->length; i>1; i--) {
        //�������̣���Ϊ��ѡ�������ֵ���б���������ͬʱ�����λ���ϵ�Ԫ�ؽ����滻��Ϊ��һ��ɸѡ��׼��
        swap(&(H->r[1]), &(H->r[i]));
        //����ɸѡ�����ֵ�Ĺ���
        HeapAdjust(H, 1, i-1);
        for (int i=1; i<=10; i++) {
        printf("%d ",H->r[i].key);
    }
    printf("\n");
    }
}

int main() {
    SqList * L=(SqList*)malloc(sizeof(SqList));
    L->length=10;
    L->r[1].key=503;
    L->r[2].key=87;
    L->r[3].key=512;
    L->r[4].key=61;
    L->r[5].key=908;
    L->r[6].key=170;
    L->r[7].key=897;
    L->r[8].key=275;
    L->r[9].key=653;
    L->r[10].key=426;
    HeapSort(L);
    for (int i=1; i<=L->length; i++) {
        printf("%d ",L->r[i].key);
    }
    return 0;
}
