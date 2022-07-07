#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define N 4
void print_matrix(int tar[][N],int n){
    int i,j;
    for(i = 0; i<n; i++){
        for(j = 0; j<N; j++){
            printf("%10d",tar[i][j]);
        }
        printf("\n");
    }
}
void trans_matrix(int tar[][N], int n){
    int tmp[N][N];
    int i,j;
    for(i = 0; i<N; i++){
        for(j = 0; j<N; j++){
            tmp[N-j-1][i] = tar[i][j];
        }
    }
    for(i = 0; i<N; i++){
        for(j = 0; j<N; j++){
            tar[i][j] = tmp[i][j];
        }
    }
}
int main(){
    int tar[N][N];
    int i,j;
//    srand(time(0));
     
    for(i = 0; i<N; i++){
        for(j = 0; j<N; j++){
//            tar[i][j] = rand()%100; //这里是随机生成的输入
            scanf("%d", &tar[i][j]);
        }
    }
    print_matrix(tar, N);
    trans_matrix(tar, N);
    printf("\n");
    print_matrix(tar, N);
    return 0;
}
