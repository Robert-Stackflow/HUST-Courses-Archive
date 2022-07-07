#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
 
int exist_in(char *arr1[][2], char *arr2[], int length);
 
int main(void)
{
    int i = 0, length;
    time_t t;
    char *person  ;
    char *computer ;
    char *computer_person[2];
    char *guess_arr[] = {"石头", "剪刀", "布"};
    char *win[3][2] = {{"布", "石头"}, {"石头", "剪刀"}, {"剪刀", "布"}};
     
    length = (int)sizeof(win)/(int)sizeof(win[0]);
 
    while (1)
    {
        srand((unsigned) time(&t));
        i = rand() % 3 ;
         
        computer = (char *)malloc(100 * sizeof(char));
        strcpy(computer,guess_arr[i] );
        printf("请输入 剪刀 石头 布:\n");
     
        person = (char *)malloc(100 * sizeof(char));
        scanf("%s", person);
     
        computer_person[0] = computer;
        computer_person[1] = person;
 
        if (strcmp(computer, person) == 0 )
        {
            printf("平手！\n");
        }
        else if (exist_in(win, computer_person, length))
        {
              printf("电脑获胜\n");
        }
        else
        {
            printf("人获胜\n");
             
            free(computer);
            free(person);   
     
            person = NULL;
            computer = NULL;
            break;
        }
         
        free(computer);
        free(person);
        person = NULL;
        computer = NULL;
 
    }
     
     
    return 0;
 }
 
int exist_in(char *arr1[][2], char *arr2[], int length)
{
    int i;
    for (i = 0; i < length; i++)
    {
        if (strcmp(arr1[i][0], arr2[0]) == 0 && strcmp(arr1[i][1], arr2[1]) == 0)
        {
            return 1;
        }
 
    }
 
    return 0;
 
 }
