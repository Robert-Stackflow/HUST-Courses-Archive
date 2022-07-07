
#include <stdio.h>
#include <stdlib.h>
#define BLOCK_SIZE 10

typedef struct {
    int *array;
    int size;
} Array;

Array array_create(int size);
void array_free(Array *a);
int* array_at(Array *a,int index);
int array_size(const Array *a);
void array_inflate(Array *a,int more_size);


int main(int argc, const char * argv[])
{
    Array a = array_create(2);
    printf("a.init_size = %d\n",array_size(&a));
    *array_at(&a, 0) = 10;
    printf("a.arry[0] = %d\n",a.array[0]);
    int number=0;
    int cnt = 0;
    while (number != -1) {
        printf("������һ������ֵ:\n");
        scanf("%d",&number);
        if (number != -1) {
            *array_at(&a, cnt) = number;
            cnt++;
        }
//        scanf("%d",array_at(&a, cnt++)); //Ҳ����
    }
    for (int i =0; i<cnt; i++) {
        printf("a.array[%i] = %d\n",i,a.array[i]);
    }
    
    array_free(&a);
    
    return 0;
}

Array array_create(int init_size){
    Array a;
    a.size = init_size;
    a.array = (int *)malloc(sizeof(int)*(a.size));
    return a;
    
}
//������ͷ�
void array_free(Array *a){
    free(a->array);
    a->array = NULL;
    a->size = 0;
}
//������Ĵ�Сsize
int array_size(const Array *a){
    return a->size;
}
//ָ��λ���������ֵ
int* array_at(Array *a,int index){
    //���index����a��size����Ҫ�������Ǵ�
    if (index >= a->size) {
        array_inflate(a, (index/BLOCK_SIZE+1)*BLOCK_SIZE - a->size);
    }
    return &(a->array[index]);

}
//���������
void array_inflate(Array *a,int more_size){
    
    int *p = (int*)malloc((a->size + more_size)*sizeof(int));
    for (int i = 0; i<a->size; i++) {
        p[i] = a->array[i];
    }
    free(a->array);
    a->array = p;
    a->size = a->size+more_size;
    
}

