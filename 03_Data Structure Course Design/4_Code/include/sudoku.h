#ifndef SUDOKU_H
#define SUDOKU_H
#include "dpll.h"
//----------the statement of the functions-------------------
void CreateSudoku(int level);
int LoadSudoku(char *FileName);
void SaveSudoku(CNF *cnf, char *FileName);
void SolveSudoku(CNF *cnf, char *FileName);
bool DFSSolver(int (*Parameter)[9], int x, int y);
bool LasVegas(int n);
void DisplaySudoku(int (*Parameter)[9]);
bool check(int (*Parameter)[9], int x, int y, int num);
bool check2(int (*Parameter)[9], int x, int y, int limit);
bool DigHole(int x, int y);
void DigHoles(int level);
int coding(int x, int y, int n);
void SuDoKu(void);
#endif