#include <stdio.h>
#include <stdlib.h>
#define BLOCK_SIZE 10

typedef struct {
    char *array;
    int size;
}Array;

Array array_create(int size);
void array_free(Array *a);
char* array_at(Array *a,int index);
int array_size(const Array *a);
void array_inflate(Array *a,int more_size);

int main(int argc, const char * argv[])
{
    Array a=array_create(2);
    *array_at(&a,0)=10;
    char check;
    int cnt=0,count=0;
    while (check!='\n') {
        scanf("%c",&check);
        if (check!='\n') {
            *array_at(&a,cnt)=check;
            cnt++;
        }
//        scanf("%d",array_at(&a, cnt++)); //也可以
    }
    for (int i =0; i<cnt/2; i++) {
    	if(a.array[i]==a.array[cnt-i-1]) count++;
    }
    if(count==cnt/2) printf("true");
    else printf("false");
    array_free(&a);
    return 0;
}

Array array_create(int init_size){
    Array a;
    a.size = init_size;
    a.array = (char *)malloc(sizeof(int)*(a.size));
    return a;
}
//数组的释放
void array_free(Array *a){
    free(a->array);
    a->array = NULL;
    a->size = 0;
}
//求数组的大小size
int array_size(const Array *a){
    return a->size;
}
//指定位置拿数组的值
char* array_at(Array *a,int index){
    //如果index大于a的size，需要将数组涨大
    if (index >= a->size) {
        array_inflate(a, (index/BLOCK_SIZE+1)*BLOCK_SIZE - a->size);
    }
    return &(a->array[index]);
}
//数组的增长
void array_inflate(Array *a,int more_size){
    
    char *p= (char*)malloc((a->size+more_size)*sizeof(char));
    for (int i = 0; i<a->size; i++) {
        p[i]= a->array[i];
    }
    free(a->array);
    a->array=p;
    a->size = a->size+more_size;
}

