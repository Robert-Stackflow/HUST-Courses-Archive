#ifndef DPLL_H
#define DPLL_H
#include "fin.h"
//----------the statement of the functions-------------------
//Prehandle the cnf and record information of the variables
void PreRecord(CNF *cnf);
//Preprocess and select decision strategy
int PreHandle(HeadNode *head, int num);
//Find single clause
int FindSingleClause(HeadNode *p);
//Delete information related to val
HeadNode *DeleteClause(HeadNode *head, int val);
//RecoverClause to backtrack
HeadNode *RecoverClause(HeadNode *head, int val);
//Decide the variable
int DecideVariable(HeadNode *head, int option);
// Determine whether it is an empty set
int EmptyClause(HeadNode *head);
//Print and display the cnf paradigm linked list
void Display(HeadNode *head);
//The main function of the Dpll algorithm
int DPLL(HeadNode *head, int option, int val, int depth);
//Save result into the file with the same name
int SaveResult(const char *FileName, int state, int time);
//Judge whether the result is correct
int JudgeResult(char *FileName);
//SAT main function
void SAT(void);
#endif