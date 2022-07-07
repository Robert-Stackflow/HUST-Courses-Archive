#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#ifndef FIN_H
#define FIN_H
#define OK 1
#define ERROR 0
#define TIMEOUT -3
#define overflow -2
#define INFEASIBLE -4
#define TIMELIMIT 180000
#define max(x, y) ((x) > (y) ? (x) : (y))

//Data structure definition of adjacency table for storing data
typedef struct ClauseNode
{
	int flag;
	int literal;
	struct ClauseNode *next;
} ClauseNode;

//The statement of the headnode of the clauses
typedef struct HeadNode
{
	int flag;
	int count;
	struct HeadNode *next;
	struct ClauseNode *horizon;
} HeadNode;

//The statement of the headnode of the clauses which contains the certain variable
typedef struct HeadList
{
	HeadNode *phead;
	ClauseNode *Var;
	struct HeadList *next;
} HeadList;

//The statement of the information of the variables
typedef struct VarValue
{
	int pos;
	int neg;
	int flag;
	int times;
	int IsInit;
	HeadList *positive;
	HeadList *negative;
} VarValue;

//The statement of the data of the cnf sample
typedef struct CNF
{
	char type[20];
	HeadNode *head;
	int clause_num;
	int literal_num;
} CNF;
//----------the statement of the functions-------------------
//load the cnf file into data structure
int LoadFile(const char *FileName, CNF *cnf);
//display the cnf data
void DisplayCNF(CNF *cnf);
//save the cnf data into the file
int SaveCNF(const char *FileName, CNF *cnf);
//destory the cnf
void DestoryCNF(CNF *cnf);
#endif