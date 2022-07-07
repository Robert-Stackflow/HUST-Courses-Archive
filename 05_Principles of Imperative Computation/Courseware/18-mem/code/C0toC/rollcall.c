#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "xalloc.h"

struct student{
    char* andrewid;
    bool* attendance;
    int num_days;
};
typedef struct student* student;

student student_new(char* id, char* att){
    student S = xmalloc(sizeof(struct student));
    S->andrewid = id;
    S->num_days = strlen(att);
    S->attendance = xmalloc(sizeof(bool) * S->num_days);
    for(int i = 0; i < S->num_days; i++){
        if(att[i] == 'T'){
            S->attendance[i] = true;
        } else{
            S->attendance[i] = false;
        }
    }
    return S;
}

int count_present(student S){
    int count = 0;
    for(int i = 0; i < S->num_days; i++){
        if(S->attendance[i]){
            count++;
        }
    }
    return count;
}

void student_free(student S){
    free(S->attendance);
    free(S);
}


int main(){
    student* S = xmalloc(sizeof(student) * 5);
    S[0] = student_new("niveditc", "TFFTT");
    S[1] = student_new("medee", "TTT");
    S[2] = student_new("shayaks", "TFTT");
    S[3] = student_new("sj1", "TFTFT");
    S[4] = student_new("hbovik", "");
    for(int i = 0; i < 5; i++){
        printf("%s : %d/%d\n", S[i]->andrewid, count_present(S[i]), S[i]->num_days);
    }

    /* Now free elements of that array and then the array itself */
    for(int i = 0; i < 5; i++){
        student_free(S[i]);
    }
    free(S);
    return 0;
}

