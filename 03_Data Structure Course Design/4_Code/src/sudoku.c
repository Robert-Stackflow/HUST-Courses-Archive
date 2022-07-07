#include"sudoku.h"
//------------Declaration of global variables----------------
int hole, every, used[3];         // secondary variables
int limit0[4] = {24, 36, 48, 60}; // the digging interval of the corresponding difficulty
int res[9][9];                    // res records the result from DPLL
int Tried[9][9];                  // Tried records which numbers have been tried to dig
int final[9][9];                  // final records sudoku final game
int Sudoku[9][9];                 // Sudoku records the Sudoku problem
int conflict[9][9];               // conflict records the conflicts generated during the suduku game
//------------Declaration of extern variables----------------
extern CNF cnf;             // cnf structure
extern VarValue *ValueList; // the data of the literal
extern char LFileName[100], SFileName[100], RFileName[100];
void printf_cyan(int num)
{
    printf("\033[0m\033[1;46m %d \033[0m", num);
}

void printf_red(int num)
{
    printf("\033[0m\033[1;5;41m %d \033[0m", num);
}

void printf_green(int num)
{
    printf("\033[0m\033[1;42m %d \033[0m", num);
}

void DisplaySudoku(int (*Parameter)[9])
{
    // Show Sudoku pattern
    printf("   1   2   3   4   5   6   7   8   9\n");
    printf(" +---+---+---+---+---+---+---+---+---+\n");
    for (int i = 0; i < 9; i++)
    {
        printf("%d|", i + 1);
        for (int j = 0; j < 9; j++)
        {
            if (Parameter[i][j] && !Tried[i][j])
                printf_cyan(Parameter[i][j]);
            else if (Parameter[i][j] && conflict[i][j] && every)
                printf_red(Parameter[i][j]);
            else if (Parameter[i][j] && Tried[i][j])
                printf_green(Parameter[i][j]);
            else
                printf("   ");
            if ((j + 1) % 3 != 0)
                printf(" ");
            if ((j + 1) % 3 == 0 && j != 8)
                printf("|");
        }
        printf("|\n");
        if ((i + 1) % 3 != 0)
            printf(" |           |           |           |\n");
        if ((i + 1) % 3 == 0 && i != 8)
            printf(" +---+---+---+---+---+---+---+---+---+\n");
    }
    printf(" +---+---+---+---+---+---+---+---+---+\n");
}

bool check(int (*Parameter)[9], int x, int y, int num)
{
    // Determine whether the number filled in at the current position violates Sudoku rules
    int i, j;
    // Judge the line
    for (i = x, j = 0; j < 9; j++)
        if (Parameter[i][j] == num && j != y)
            return false;
    // Judge the list
    for (i = 0, j = y; i < 9; i++)
        if (Parameter[i][j] == num && i != x)
            return false;
    // Judge the little Jiugongge
    for (i = (x / 3) * 3; i < (x / 3) * 3 + 3; i++)
        for (j = (y / 3) * 3; j < (y / 3) * 3 + 3; j++)
            if (Parameter[i][j] == num && i != x && j != y)
                return false;
    return true;
}

bool check2(int (*Parameter)[9], int x, int y, int limit)
{
    // Determine whether the current digging operation violates the digging restrictions
    int i, j, num = 0;
    for (i = x, j = 0; j < 9; j++)
        if (Parameter[i][j])
            num++;
    if (num <= limit)
        return false;
    num = 0;
    for (i = 0, j = y; i < 9; i++)
        if (Parameter[i][j])
            num++;
    if (num <= limit)
        return false;
    return true;
}

int nextx(int x, int y)
{
    // Auxiliary function of DFSSlover to generate abscissa
    if (y == 8)
        return x + 1;
    return x;
}

int nexty(int x, int y)
{
    // Auxiliary function of DFSSlover to generate ordinate
    if (y == 8)
        return 0;
    return y + 1;
}

bool DFSSolver(int (*Parameter)[9], int x, int y)
{
    // Depth first search solver
    if (x > 8)
    {
        // Conditions for exiting the solver
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++)
                Sudoku[i][j] = Parameter[i][j];
        return 1;
    }
    if (Sudoku[x][y] != 0) // If it has been filled in, continue to solve
        return DFSSolver(Parameter, nextx(x, y), nexty(x, y));
    int copyd[9][9], flag = 0;
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            copyd[i][j] = Parameter[i][j];
    for (int i = 1; i < 10; i++)
    {
        if (check(Parameter, x, y, i))
        {
            // If it does not violate the rules, fill in and continue to solve
            copyd[x][y] = i;
            if (DFSSolver(copyd, nextx(x, y), nexty(x, y)))
            {
                flag = 1;
                break;
            }
        }
    }
    return flag;
}

bool LasVegas(int n)
{
    // Use the Las Vegas random algorithm to generate a random Sudoku final game
    for (int i = 1; i <= n; i++)
    {
        int num = rand() % 81;
        int x = num / 9, y = num % 9;
        while (1)
        {
            while (!(Sudoku[x][y] = rand() % 9))
                Sudoku[x][y] = rand() % 9;
            if (check(Sudoku, x, y, Sudoku[x][y]))
                break;
        }
    }
    if (DFSSolver(Sudoku, 0, 0))
        return true;
    return false;
}

bool DigHole(int x, int y)
{
    Tried[x][y] = 1;                   // Mark as tried
    int temp = Sudoku[x][y], flag = 1; // Record the number before attempt
    for (int i = 1; i <= 9; i++)
    {
        if (i != temp)
        {
            // All except the initial number are traversed
            if (check(Sudoku, x, y, i))
            {
                // If the number does not violate the rules after filling in
                Sudoku[x][y] = i;
                int copyd[9][9], flag = 0;
                for (int i = 0; i < 9; i++)
                    for (int j = 0; j < 9; j++)
                        copyd[i][j] = Sudoku[i][j];
                // Update Sudoku with this number and use the solver to solve
                if (DFSSolver(Sudoku, 0, 0))
                {
                    // Once there is a solution, mark that number cannot be digged
                    // Exit the loop
                    flag = 0;
                    for (int i = 0; i < 9; i++)
                        for (int j = 0; j < 9; j++)
                            Sudoku[i][j] = copyd[i][j];
                    break;
                }
            }
        }
    }
    if (!flag) // If there are multiple solutions after digging, go back to the initial value
        Sudoku[x][y] = temp;
    else // Otherwise dig out the number and update the count variable
        Sudoku[x][y] = 0;
    if (!flag)
        return false;
    else
        return true;
}

void DigHoles(int level)
{
    int holes;                    // The holes is the lower limit of the number of randomly generated digging holes corresponding to the difficulty
    int count = 0;                // The count records the number of holes that have been dug
    int limit1[4] = {6, 5, 4, 2}; // The array limit2 represents the minimum number of holes not dug in each row or column
    // Generate the number of digging holes suitable for the selected difficulty level
    holes = rand() % 52;
    while (!(holes >= limit0[level - 1] && holes < limit0[level]))
        holes = rand() % 52;
    hole = holes;
    // Choose the digging strategy according to the difficulty level
    switch (level)
    {
    case 1:
    case 2:
    case 3:
        count = 0;
        // Random way to dig holes
        while (count < holes)
        {
            // Randomly generate digging coordinates
            int order = rand() % 81;
            while (!check2(Sudoku, order / 9, order % 9, limit1[level]))
                order = rand() % 81;
            // Skip if already tried
            if (Tried[order / 9][order % 9])
                continue;
            else if (DigHole(order / 9, order % 9))
                count++;
        }
        break;
    case 4:
        count = 0;
        // Digging in a serpentine way
        for (int i = 0; i < 9; i++)
        {
            if (i % 2)
            {
                for (int j = 8; j >= 0; j--)
                {
                    if (check2(Sudoku, i, j, limit1[level]))
                    {
                        if (Tried[i][j])
                            continue;
                        else if (DigHole(i, j))
                            count++;
                        if (count >= holes)
                            break;
                    }
                }
            }
            else
            {
                for (int j = 0; j < 9; j++)
                {
                    if (check2(Sudoku, i, j, limit1[level]))
                    {
                        if (Tried[i][j] && count >= holes)
                            continue;
                        else if (DigHole(i, j))
                            count++;
                        if (count >= holes)
                            break;
                    }
                }
            }
            if (count >= holes)
                break;
        }
        break;
    }
}

void CreateSudoku(int level)
{
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            Sudoku[i][j] = 0, final[i][j] = 0, Tried[i][j] = 0, res[i][j] = 0;
    srand(time(NULL));
    // Sudoku final
    int t1 = clock();
    while (!LasVegas(11))
        ;
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            final[i][j] = Sudoku[i][j];
    // Dig holes to generate Sudoku
    DigHoles(level);
    int t2 = clock();
    used[0] = t2 - t1;
}

int LoadSudoku(char *FileName)
{
    FILE *fp = fopen(FileName, "r");
    if (!fp)
        return INFEASIBLE;
    if (FileName[strlen(FileName) - 1] == 's' && FileName[strlen(FileName) - 2] == 's' && FileName[strlen(FileName) - 3] == '.')
    { // if the file is FILE.ss,load the file directly
        char c;
        int i = 0, j = 0;
        while (fread(&c, sizeof(char), 1, fp))
        {
            if (c >= '1' && c <= '9')
                Sudoku[i][j++] = c - '0';
            else if (c == '\n' || c == '!')
                continue;
            else if (c == '.')
                Sudoku[i][j++] == 0;
            if (j == 8)
                i++, j = -1;
        }
    }
    else if (FileName[0] == 's' && FileName[1] == 'u' && FileName[2] == 'd')
    { // if the file is sudNUM.cnf,load the comments of the file
        char c;
        int i = 0, j = 0, flag = 0;
        while (fread(&c, sizeof(char), 1, fp))
        {
            // read the content of the notes
            if (c == 'c')
                flag++;
            if (flag == 2)
                break;
        }
        while (i != 9)
        {
            fgetc(fp);
            fgetc(fp);
            c = fgetc(fp);
            while (c != '\n')
            {
                if (c >= '1' && c <= '9')
                    Sudoku[i][j++] = c - '0';
                else if (c == '.')
                    Sudoku[i][j++] == 0;
                c = fgetc(fp);
            }
            i++;
            j = 0;
        }
    }
    else if (strcmp(FileName, "Sudoku.cnf") == 0)
    { // if the file is generated by the exe,load the comments of the file differently
        char c;
        int i = 0, j = 0, flag = 0;
        while (fread(&c, sizeof(char), 1, fp))
        {
            // read the content of the notes
            if (c == 'c')
                flag++;
            if (flag == 3)
                break;
        }
        fgetc(fp);
        while (i != 9)
        {
            fgetc(fp);
            fgetc(fp);
            for (j = 0; j < 9; j++)
                fscanf(fp, "%d", &Sudoku[i][j]);
            i++;
            fgetc(fp);
        }
    }
    fclose(fp);
    return OK;
}

int coding(int x, int y, int n)
{
    return (x - 1) * 81 + (y - 1) * 9 + n;
}

void SaveSudoku(CNF *cnf, char *FileName)
{
    int t1 = clock();
    FILE *fp = fopen(FileName, "wb");
    int tip = 0;
    fprintf(fp, "c\nc Sudoku Puzzle\nc\n");
    for (int i = 0; i < 9; i++)
    {
        fprintf(fp, "c ");
        for (int j = 0; j < 9; j++)
        {
            fprintf(fp, "%d ", Sudoku[i][j]);
            if (Sudoku[i][j])
                tip++;
        }
        fprintf(fp, "\n");
    }
    fprintf(fp, "p cnf 729 %d\n", tip + 9801);
    for (int i = 1; i <= 9; i++)
    {
        // Only one number can be filled in each cell
        for (int j = 1; j <= 9; j++)
        {
            for (int k = 1; k <= 9; k++)
                fprintf(fp, "%d ", coding(i, j, k));
            fprintf(fp, "0\n");
            for (int m = 1; m <= 9; m++)
                for (int n = m + 1; n <= 9; n++)
                    fprintf(fp, "%d %d 0\n", -coding(i, j, m), -coding(i, j, n));
        }
    }
    for (int i = 1; i <= 9; i++)
    {
        // Row constraint
        for (int j = 1; j <= 9; j++)
        {
            for (int k = 1; k <= 9; k++)
                fprintf(fp, "%d ", coding(i, k, j));
            fprintf(fp, "0\n");
        }
        for (int j = 1; j <= 9; j++)
        {
            for (int m = 1; m <= 9; m++)
                for (int n = m + 1; n <= 9; n++)
                    fprintf(fp, "%d %d 0\n", -coding(i, m, j), -coding(i, n, j));
        }
    }
    for (int i = 1; i <= 9; i++)
    {
        // Row constraint
        for (int j = 1; j <= 9; j++)
        {
            for (int k = 1; k <= 9; k++)
                fprintf(fp, "%d ", coding(k, i, j));
            fprintf(fp, "0\n");
        }
        for (int j = 1; j <= 9; j++)
        {
            for (int m = 1; m <= 9; m++)
                for (int n = m + 1; n <= 9; n++)
                    fprintf(fp, "%d %d 0\n", -coding(m, i, j), -coding(n, i, j));
        }
    }
    int xbox[10] = {0, 1, 1, 1, 4, 4, 4, 7, 7, 7}, ybox[10] = {0, 1, 4, 7, 1, 4, 7, 1, 4, 7};
    for (int box = 1; box <= 9; box++)
    {
        // 3*3 box constraint
        for (int k = 1; k <= 9; k++)
        {
            for (int i = xbox[box]; i <= xbox[box] + 2; i++)
            {
                for (int j = ybox[box]; j <= ybox[box] + 2; j++)
                    fprintf(fp, "%d ", coding(i, j, k));
            }
            fprintf(fp, "0\n");
        }
        for (int k = 1; k <= 9; k++)
            for (int i = xbox[box]; i <= xbox[box] + 2; i++)
                for (int m = ybox[box]; m <= ybox[box] + 2; m++)
                    for (int n = m + 1; n <= ybox[box] + 2; n++)
                        fprintf(fp, "%d %d 0\n", -coding(i, m, k), -coding(i, n, k));
    }
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            if (Sudoku[i][j])
                fprintf(fp, "%d 0\n", coding(i + 1, j + 1, Sudoku[i][j]));
    fprintf(fp, "c\nc Sudoku Final Answer\nc\n");
    for (int i = 0; i < 9; i++)
    {
        fprintf(fp, "c ");
        for (int j = 0; j < 9; j++)
        {
            fprintf(fp, "%d ", final[i][j]);
            if (final[i][j])
                tip++;
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
    int t2 = clock();
    used[1] = t2 - t1;
}

void SolveSudoku(CNF *cnf, char *FileName)
{
    PreRecord(cnf);
    int t1 = clock();
    DPLL(cnf->head, 4, DecideVariable(cnf->head, 4), 1);
    int t2 = clock();
    used[2] = t2 - t1;
    SaveResult(FileName, 1, t2 - t1);
    for (int i = 1; i <= cnf->literal_num; i++)
    {
        int x, y, n;
        x = (i - 1) / 81;
        y = (i - x * 81 - 1) / 9;
        n = i - x * 81 - y * 9;
        if (ValueList[i].flag > 0)
            res[x][y] = n;
    }
}

void SuDoKu(void)
{
    int op = 1;
    int flag = 1;
    int option = 1;
    int x = 0, y = 0, num = 0;
    int level, finish, finish2;
    char SFileName[100] = "Sudoku.cnf";
    while (op)
    {
        system("cls");
        printf("**        Menu for Sudoku problem       	\n");
        printf("--------------------------------------------\n");
        printf("0.Exit		1. Game		2. File   			\n");
        printf("--------------------------------------------\n");
        printf("Please Input Your Option[0-2]:");
        scanf("%d", &op);
        if (op == 1)
        {
            system("cls");
            printf("***                      Sudoku Game Tips                        	 \n");
            printf("---------------------------------------------------------------------\n");
            printf("1.可选择难度等级(1-3难度递增，0表示退出)                               \n");
            printf("2.可选择游戏过程中是否提示冲突(1/0)                              	   \n");
            printf("3.中途可通过输入“0 0 0”退出游戏并查看答案                          	   \n");
            printf("4.填写完成后如果错误可选择是否继续游戏(1/0)                             \n");
            printf("5.通过填写横纵坐标和数字来填数，数字为0时表示清空，为-1时表示提示数字     \n");
            printf("---------------------------------------------------------------------\n");
            printf("Please Input The Difficulty Level:");
            scanf("%d", &level);
            if (!level)
                continue;
            printf("\nPlease Choose Whether To Get Tips Before Success:");
            scanf("%d", &every);
            CreateSudoku(level);
            SaveSudoku(&cnf, SFileName);
            LoadFile(SFileName, &cnf);
            strcpy(RFileName, SFileName);
            RFileName[strlen(RFileName) - 1] = 's';
            RFileName[strlen(RFileName) - 2] = 'e';
            RFileName[strlen(RFileName) - 3] = 'r';
            SolveSudoku(&cnf, RFileName);
            flag = 1;
            while (flag)
            {
                system("cls");
                DisplaySudoku(Sudoku);
                printf("\nPlease Input Your Answer:");
                scanf("%d%d%d", &x, &y, &num);
                // Enter "0 0 0" to exit the game
                if (!x && !y && !num)
                {
                    for (int i = 0; i < 9; i++)
                        for (int j = 0; j < 9; j++)
                            conflict[i][j] = 0;
                    system("cls");
                    DisplaySudoku(res);
                    getchar(), getchar();
                    break;
                }
                // Can't modify the original Numbers
                if (!Tried[x - 1][y - 1])
                {
                    printf("Can't modify the original pattern of sudoku\n");
                    getchar(), getchar();
                    continue;
                }
                // Determine the conflict
                if (check(Sudoku, x - 1, y - 1, num) == false)
                    conflict[x - 1][y - 1] = 1;
                else
                    conflict[x - 1][y - 1] = 0;
                // The assignment
                if (num == -1)
                    Sudoku[x - 1][y - 1] = res[x - 1][y - 1];
                else
                    Sudoku[x - 1][y - 1] = num;
                if (!num)
                    hole++;
                else
                    hole--;
                // When sudoku is filled automatically after judgment is correct, if not indicates whether to check the correct answer
                if (!hole)
                {
                    for (int i = 0; i < 9; i++)
                        for (int j = 0; j < 9; j++)
                            if (Sudoku[i][j] != res[i][j])
                                flag = 0;
                    if (!flag)
                    {
                        // If it's not right
                        printf("ERROR!\n");
                        flag = 1;
                        printf("Please Choose Whether To Finish To Check The Answer:");
                        scanf("%d", &finish2);
                        if (finish2)
                        {
                            for (int i = 0; i < 9; i++)
                                for (int j = 0; j < 9; j++)
                                    conflict[i][j] = 0;
                            system("cls");
                            DisplaySudoku(final);
                            getchar(), getchar();
                            break;
                        }
                        else
                            getchar(), getchar();
                    }
                    else
                    {
                        // If the correct
                        system("cls");
                        DisplaySudoku(Sudoku);
                        printf("\n\033[0m\033[1;5;31mCongratulations!\033[0m");
                        getchar(), getchar();
                        break;
                        system("cls");
                    }
                }
            }
        }
        else if (op == 2)
        {
            while (option)
            {
                system("cls");
                printf("***       Menu for Sudoku problem       	\n");
                printf("--------------------------------------------\n");
                printf("1. CreateSudoku		2. LoadSudoku			\n");
                printf("3. SolveSudoku		0. Exit					\n");
                printf("--------------------------------------------\n");
                printf("Please Input Your Option[0-3]:");
                scanf("%d", &option);
                switch (option)
                {
                case 1:
                    printf("Please Input The Difficulty Level:");
                    scanf("%d", &level);
                    CreateSudoku(level);
                    DisplaySudoku(Sudoku);
                    printf("The Number Of Digged Holes: %d\n", hole);
                    printf("Time Used During Creating the Sudoku: %d ms\n", used[0]);
                    SaveSudoku(&cnf, SFileName);
                    LoadFile(SFileName, &cnf);
                    printf("Time Used During Saving the Sudoku: %d ms\n", used[1]);
                    getchar();
                    getchar();
                    break;
                case 2:
                    printf("Please Input The FilePath:");
                    scanf("%s", LFileName);
                    if (LoadSudoku(LFileName) == INFEASIBLE)
                        printf("File Open ERROR!\n");
                    else
                    {
                        DisplaySudoku(Sudoku);
                        SaveSudoku(&cnf, LFileName);
                        LoadFile(LFileName, &cnf);
                    }
                    getchar();
                    getchar();
                    break;
                case 3:
                    strcpy(RFileName, SFileName);
                    RFileName[strlen(RFileName) - 1] = 's';
                    RFileName[strlen(RFileName) - 2] = 'e';
                    RFileName[strlen(RFileName) - 3] = 'r';
                    SolveSudoku(&cnf, RFileName);
                    DisplaySudoku(res);
                    printf("Time Used During Solving the Sudoku: %d ms\n", used[2]);
                    getchar();
                    getchar();
                    break;
                }
            }
        }
    }
}