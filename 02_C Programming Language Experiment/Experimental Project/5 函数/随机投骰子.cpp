#include<stdlib.h>
#include<stdio.h>
void diceGame(int randSeed)
{
	srand(randSeed);
	int num1,num2,num,i=0,dice1,dice2,goal;
	dice1=rand()%6+1;
	dice2=rand()%6+1;
	num1=dice1+dice2;
	goal=num1;
	if(num1==7||num1==11){
		printf("Round 1:  Score:%d  Success!\n",num1);
		
	}
    else if(num1==2||num1==2||num1==12){
        printf("Round 1:  Score:%d  Failed!\n",num1);
    }

	else{
		printf("Round 1:  Score:%d  Continue!\n",num1); 
		printf("Next rounds: Score %d:Success, Score 7:Failed, others:Continue\n",goal);
		i=2;
		dice1=rand()%6+1;
	    dice2=rand()%6+1;
	    num=dice1+dice2;
	    while(num!=goal){
	    	if(num==7){
	    		printf("Round %d:  Score:7  Failed!\n",i);
	    		break;
			}
			else{
			printf("Round %d:  Score:%d  Continue!\n",i,num);
	    	dice1=rand()%6+1;
	    	dice2=rand()%6+1;
	    	num=dice1+dice2;
			}
	    	i++;
		}
	    if(num!=7){
			printf("Round %d:  Score:%d  Success!\n",i,goal);
		}
	}
}
int main()
{
	int randSeed;
    scanf("%d",&randSeed);        //输入整数作为随机数种子
    diceGame(randSeed);
    return 0;
}

