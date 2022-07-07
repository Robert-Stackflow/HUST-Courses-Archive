#include "sudoku.h"
int main(void)
{
	int op = 1;
	while (op)
	{
		system("cls");
		printf("*         Menu for SAT problem              \n");
		printf("--------------------------------------------\n");
		printf("0.Exit		1. CNF		2. Sudoku  			\n");
		printf("--------------------------------------------\n");
		printf("Please Input your option[0-2]:");
		scanf("%d", &op);
		if (op == 1)
			SAT();
		else if (op == 2)
			SuDoKu();
	}
	return 0;
} //end of main