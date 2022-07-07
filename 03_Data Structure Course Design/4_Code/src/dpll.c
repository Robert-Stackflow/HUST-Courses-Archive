#include "dpll.h"
//------------Declaration of global variables----------------
CNF cnf;               // cnf structure
double OptRate;        // optimization rate
int t1, t2, t3, t4;    // variables recording the time
VarValue *ValueList;   // the data of the literal
int *stack, StackSize; // stack for backtracking
int *timesort, *chart; // secondary array
int ans[2],state, reg;
char LFileName[100], SFileName[100], RFileName[100];
void PreRecord(CNF *cnf)
{
    // Initiate the ValueList
    ValueList = (VarValue *)malloc(sizeof(VarValue) * (cnf->literal_num + 1));
    for (int i = 0; i <= cnf->literal_num; i++)
    {
        ValueList[i].IsInit = 0;
        ValueList[i].times = ValueList[i].neg = ValueList[i].pos = 0;
        ValueList[i].flag = 0;
        ValueList[i].positive = NULL;
        ValueList[i].negative = NULL;
    }
    // Assign the ValueList
    HeadNode *p = cnf->head;
    ClauseNode *q;
    while (p)
    {
        q = p->horizon;
        while (q)
        {
            ValueList[abs(q->literal)].times++;
            HeadList *temp = (HeadList *)malloc(sizeof(HeadList));
            temp->phead = p;
            temp->Var = q;
            temp->next = NULL;
            if (q->literal > 0)
            {
                ValueList[abs(q->literal)].pos++;
                temp->next = ValueList[abs(q->literal)].positive;
                ValueList[abs(q->literal)].positive = temp;
            }
            else
            {
                ValueList[abs(q->literal)].neg++;
                temp->next = ValueList[abs(q->literal)].negative;
                ValueList[abs(q->literal)].negative = temp;
            }
            q = q->next;
        }
        p = p->next;
    }
}

int PreHandle(HeadNode *head, int num)
{
    // chart records the occurrence of every literal
    timesort = (int *)malloc(sizeof(int) * (num + 1));
    for (int i = 0; i <= num; i++)
        timesort[i] = i + 1;
    // count records the amount of the same occurrence
    int count[1001] = {0}, amount[1001] = {0};
    int variety = 0, maxn = -1, decision;
    // count the timesort array
    for (int i = 0; i < num; i++)
    {
        for (int j = i + 1; j <= num; j++)
        {
            if (ValueList[timesort[i]].times < ValueList[timesort[j - 1]].times)
            {
                int temp = timesort[i];
                timesort[i] = timesort[j - 1];
                timesort[j - 1] = temp;
            }
        }
    }
    // count the variety and maxn
    for (int i = 1; i <= num; i++)
        count[ValueList[i].times]++;
    for (int i = 0; i < 1001; i++)
        if (count[i])
            amount[count[i]]++;
    for (int i = 0; i < 1001; i++)
        if (amount[i])
            variety++, maxn = max(maxn, amount[i]);
    // choose the strategy
    if (variety <= 2)
        decision = 3;
    else if (variety >= 16)
        decision = 4;
    else if (variety < 10 && maxn >= 4)
        decision = 1;
    else
        decision = 2;
    return decision;
}

int FindSingleClause(HeadNode *p)
{
    // If there is a clause with a clause node number of 1 in the linked list, it means that there is a single clause
    while (p)
    {
        if (p->count == 1 && p->flag == 0)
        {
            ClauseNode *q = p->horizon;
            while (q)
            {
                if (q->flag == 0)
                    return q->literal;
                q = q->next;
            }
        }
        p = p->next;
    }
    return 0;
}

HeadNode *DeleteClause(HeadNode *head, int val)
{
    HeadList *ptr;
    // Delete the "same" clause
    if (val > 0)
        ptr = ValueList[abs(val)].positive;
    else
        ptr = ValueList[abs(val)].negative;
    while (ptr)
    {
        HeadNode *p = ptr->phead;
        if (p->flag == 0)
        {
            p->flag = abs(val);
            cnf.clause_num--;
            ClauseNode *q = p->horizon;
            while (q)
            {
                if (q->flag == 0)
                {
                    q->flag = abs(val);
                    ValueList[abs(q->literal)].times--;
                    if (q->literal > 0)
                        ValueList[abs(q->literal)].pos--;
                    else
                        ValueList[abs(q->literal)].neg--;
                    p->count--;
                }
                q = q->next;
            }
        }
        ptr = ptr->next;
    }
    // Delete the "different" literal
    if (val < 0)
        ptr = ValueList[abs(val)].positive;
    else
        ptr = ValueList[abs(val)].negative;
    while (ptr)
    {
        ClauseNode *q = ptr->Var;
        if (q->flag == 0)
        {
            q->flag = abs(val);
            ValueList[abs(q->literal)].times--;
            if (q->literal > 0)
                ValueList[abs(q->literal)].pos--;
            else
                ValueList[abs(q->literal)].neg--;
            ptr->phead->count--;
        }
        ptr = ptr->next;
    }
    return head;
}

HeadNode *RecoverClause(HeadNode *head, int val)
{
    HeadList *ptr;
    // Recover the "same" clause
    if (val > 0)
        ptr = ValueList[abs(val)].positive;
    else
        ptr = ValueList[abs(val)].negative;
    while (ptr)
    {
        HeadNode *p = ptr->phead;
        if (p->flag == abs(val))
        {
            p->flag = 0;
            cnf.clause_num--;
            ClauseNode *q = p->horizon;
            while (q)
            {
                if (q->flag == abs(val))
                {
                    q->flag = 0;
                    ValueList[abs(q->literal)].times++;
                    if (q->literal > 0)
                        ValueList[abs(q->literal)].pos++;
                    else
                        ValueList[abs(q->literal)].neg++;
                    p->count++;
                }
                q = q->next;
            }
        }
        ptr = ptr->next;
    }
    // Recover the "different" literal
    if (val < 0)
        ptr = ValueList[abs(val)].positive;
    else
        ptr = ValueList[abs(val)].negative;
    while (ptr)
    {
        ClauseNode *q = ptr->Var;
        if (q->flag == abs(val))
        {
            q->flag = 0;
            ValueList[abs(q->literal)].times++;
            if (q->literal > 0)
                ValueList[abs(q->literal)].pos++;
            else
                ValueList[abs(q->literal)].neg++;
            ptr->phead->count++;
        }
        ptr = ptr->next;
    }
    return head;
}

int EmptyClause(HeadNode *head)
{
    // Returns true if it contains an empty clause, false if it does not
    HeadNode *p = head;
    while (p)
    {
        if (p->count == 0 && p->flag == 0)
            return true;
        p = p->next;
    }
    return false;
}

// a series of functions used to decide variables
int Decide_0(HeadNode *head)
{
    // Return the first literal in the list
    HeadNode *p = head;
    while (p)
    {
        if (p->flag == 0)
        {
            ClauseNode *q = p->horizon;
            while (q)
            {
                if (q->flag == 0)
                    return q->literal;
                q = q->next;
            }
        }
        p = p->next;
    }
    return 0;
}

int Decide_1(HeadNode *head)
{
    // Return the most frequent occurrences of the text every time after DPLL
    int maxn = -1, flag;
    for (int i = 1; i <= cnf.literal_num; i++)
        if (ValueList[i].IsInit == 0)
            if (maxn < ValueList[i].times)
                maxn = ValueList[i].times, flag = i;
    if (ValueList[flag].pos > ValueList[flag].neg)
        return flag;
    else
        return -flag;
}

int Decide_2(HeadNode *head)
{
    // Return the most unassigned positive literal in the original data
    for (int i = 0; i < cnf.literal_num; i++)
        if (ValueList[timesort[i]].IsInit == 0)
            return timesort[i];
    return 0;
}

int Decide_3(HeadNode *head)
{
    // Return the first literal in the list
    HeadNode *p = head;
    while (p)
    {
        if (p->flag == 0)
        {
            ClauseNode *q = p->horizon;
            while (q)
            {
                if (q->flag == 0)
                    return q->literal;
                q = q->next;
            }
        }
        p = p->next;
    }
    return 0;
}

int Decide_4(HeadNode *head)
{
    // Return the first unassigned literal in the list
    for (int i = 1; i <= cnf.literal_num; i++)
        if (ValueList[i].IsInit == 0)
            return i;
    return 0;
}

int DecideVariable(HeadNode *head, int option)
{
    switch (option)
    {
    case 0:
        return Decide_0(head);
        break;
    case 1:
        return Decide_1(head);
        break;
    case 2:
        return Decide_2(head);
        break;
    case 3:
        return Decide_3(head);
        break;
    case 4:
        return Decide_4(head);
        break;
    }
    return 0;
}

void Display(HeadNode *head)
{
    HeadNode *q = NULL;
    ClauseNode *p = NULL;
    q = head;
    while (q)
    {
        if (q->flag == 0)
        {
            printf("%3d: ", q->count);
            p = q->horizon;
            while (p)
            {
                if (p->flag == 0)
                    printf("%6d ", p->literal);
                p = p->next;
            }
            printf("\n");
        }
        q = q->next;
    }
}

int DPLL(HeadNode *head, int option, int val, int depth)
{
    if (!head)
        return INFEASIBLE;
    // use CLOCK function to meet the time limit
    if (clock() - t1 > TIMELIMIT)
        return TIMEOUT;
    // Single clause rule
    int order;
    depth == 1 ? (order = 0) : (order = val);
    // Find the single clause(s)
    while (order)
    {
        // push into the stack
        stack = (int *)realloc(stack, sizeof(int) * (StackSize + 1));
        stack[StackSize++] = order;
        // Delete related clause
        head = DeleteClause(head, order);
        // assign the value
        if (order > 0)
            ValueList[abs(order)].flag = 1;
        else
            ValueList[abs(order)].flag = -1;
        ValueList[abs(order)].IsInit = 1;
        if (EmptyClause(head))
        {
            // backtrack if there is an empty clause
            for (; stack[StackSize - 1] != val; StackSize--)
                RecoverClause(head, stack[StackSize - 1]), ValueList[abs(stack[StackSize - 1])].IsInit = 0;
            RecoverClause(head, stack[StackSize - 1]);
            ValueList[abs(stack[StackSize - 1])].IsInit = 0;
            StackSize--;
            return false;
        }
        // Satisfied if the clause set is empty
        if (DecideVariable(head, 0) == 0)
            return true;
        order = FindSingleClause(head);
    }
    // Split strategy
    int v = DecideVariable(head, option);
    if (!v)
        return true;
    // Add a single clause containing only the argument v in the current linked list, and perform DPLL search
    int a = DPLL(head, option, v, 2);
    if (a == true)
        return true;
    else if (a == TIMEOUT)
        return TIMEOUT;
    if (DPLL(head, option, -v, 2) == true)
        return true;
    else
    {
        // backtrack to procceed other functions
        if (StackSize == 0)
            return false;
        for (; stack[StackSize - 1] != val; StackSize--)
            RecoverClause(head, stack[StackSize - 1]), ValueList[abs(stack[StackSize - 1])].IsInit = 0;
        RecoverClause(head, stack[StackSize - 1]);
        ValueList[abs(stack[StackSize - 1])].IsInit = 0;
        StackSize--;
        return false;
    }
    // Go back to the initial state of executing the branch strategy on v and enter another branch
}

int SaveResult(const char *FileName, int state, int time)
{
    FILE *fp;
    if ((fp = fopen(FileName, "wb")) == NULL)
        return INFEASIBLE;
    else
    {
        fprintf(fp, "s %d\n", state);
        if (state == 1)
        {
            fprintf(fp, "v ");
            for (int i = 1; i <= cnf.literal_num; i++)
                fprintf(fp, "%d ", ValueList[i].flag * i);
            fprintf(fp, "\n");
        }
        fprintf(fp, "t %d", time);
        fclose(fp);
    }
    return OK;
}

int JudgeResult(char *FileName)
{
    int res[cnf.literal_num + 1];
    FILE *fin = fopen(FileName, "r");
    if (!fin)
        return INFEASIBLE;
    int temp;
    fgetc(fin);
    fscanf(fin, "%d", &temp);
    if (temp != 1)
        return INFEASIBLE;
    if (temp == 1)
    {
        fgetc(fin);
        fgetc(fin);
        for (int i = 1; i <= cnf.literal_num; i++)
            fscanf(fin, "%d", &res[i]);
        printf("The answer read from the file:\n");
        for (int i = 1; i <= cnf.literal_num; i++)
            printf("%d ", res[i]);
        int flag = 0;
        HeadNode *p = cnf.head;
        ClauseNode *q;
        while (p)
        {
            printf("\n");
            flag = 0;
            q = p->horizon;
            while (q)
            {
                int sign = (res[abs(q->literal)] / abs(q->literal)) * (q->literal / abs(q->literal));
                printf("%3d ", sign);
                if (sign >= 0)
                    flag = 1;
                q = q->next;
            }
            if (!flag)
                return ERROR;
            p = p->next;
        }
        if (!flag)
            return ERROR;
    }
    fclose(fin);
    return OK;
}

void SAT()
{
    int decision;
    int option = 1;
    HeadNode *p = NULL;
    ClauseNode *q = NULL;
    while (option)
    {
        system("cls");
        printf("**        Menu for CNF problem              \n");
        printf("--------------------------------------------\n");
        printf("1. LoadFile		2. DisplayCNF				\n");
        printf("3. SaveCNF		4. DestroyCNF				\n");
        printf("5. DPLL			6. ImoprovedDPLL			\n");
        printf("7. JudgeResult  \t0. Exit					\n");
        printf("--------------------------------------------\n");
        printf("Please Input your option[0-7]:");
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            printf("Please Input The FilePath:");
            scanf("%s", LFileName);
            reg = LoadFile(LFileName, &cnf);
            if (reg == INFEASIBLE)
                printf("File Open Error!");
            else
            {
                printf("File Open Success!\n");
                PreRecord(&cnf);
                decision = PreHandle(cnf.head, cnf.literal_num);
            }
            getchar();
            getchar();
            break;
        case 2:
            DisplayCNF(&cnf);
            getchar();
            getchar();
            break;
        case 3:
            printf("Please Input The FilePath:");
            scanf("%s", SFileName);
            reg = SaveCNF(SFileName, &cnf);
            if (reg == INFEASIBLE)
                printf("File Open Error!");
            else
                printf("File Write Success!");
            getchar();
            getchar();
            break;
        case 4:
            DestoryCNF(&cnf);
            getchar();
            getchar();
            break;
        case 5:
            t1 = clock();
            ans[0] = DPLL(cnf.head, 0, DecideVariable(cnf.head, 0), 1);
            t2 = clock();
            t3 = (t2 - t1);
            if (ans[0] == INFEASIBLE)
                printf("CNF Is Empty!\n");
            else if (ans[0] == true)
                state = 1, printf("Satisfied!\n");
            else if (ans[0] == false)
                state = 0, printf("Unsatisfied!\n");
            else
                state = -1, printf("Timeout!\n");
            if (ans[0] != INFEASIBLE)
                printf("Time: %d ms\n", t3);
            if (ans[0] == true)
            {
                printf("\nThe answer is set out below:\n");
                for (int i = 1; i <= cnf.literal_num; i++)
                {
                    if (ValueList[i].flag == -1)
                        printf("The value of the variable %3d is 0\n", i);
                    else
                        printf("The value of the variable %3d is 1\n", i);
                }
            }
            if (ans[0] != INFEASIBLE)
            {
                strcpy(RFileName, LFileName);
                RFileName[strlen(RFileName) - 1] = 's';
                RFileName[strlen(RFileName) - 2] = 'e';
                RFileName[strlen(RFileName) - 3] = 'r';
                SaveResult(RFileName, state, t3);
            }
            getchar();
            getchar();
            break;
        case 6:
            // reset the cnf list
            p = cnf.head;
            int count;
            while (p)
            {
                count = 0;
                p->flag = 0;
                q = p->horizon;
                while (q)
                {
                    q->flag = 0;
                    count++;
                    q = q->next;
                }
                p->count = count;
                p = p->next;
            }
            PreRecord(&cnf);
            t1 = clock();
            int choice = DecideVariable(cnf.head, decision);
            printf("The Decision:%d\n", decision);
            ans[1] = DPLL(cnf.head, decision, choice, 1);
            t2 = clock();
            t4 = (t2 - t1);
            if (ans[1] == INFEASIBLE)
                printf("CNF Is Empty!\n");
            else if (ans[1] == true)
                state = 1, printf("Satisfied!\n");
            else if (ans[1] == false)
                state = 0, printf("Unsatisfied!\n");
            else
                state = -1, printf("Timeout!\n");
            printf("Time before Optimized: %d ms\nTime after Optimized: %d ms\n\n", t3, t4);
            // Timeout before optimized and success after optimized
            if (ans[0] == TIMEOUT && ans[1] != TIMEOUT)
                printf("Optimization rate: 100.00%\n");
            // Timeout all the way
            else if (ans[0] == TIMEOUT && ans[1] == TIMEOUT)
                continue;
            // The DPLL is optimized successfully
            else if (t3 > t4)
            {
                OptRate = (t3 - t4) / t3;
                printf("Optimization rate: %.2f%\n", OptRate * 100);
            }
            // The optimization is a failure
            else
                printf("Optimization failed!\n");
            if (ans[1] == true)
            {
                printf("\nThe answer is set out below:\n");
                for (int i = 1; i <= cnf.literal_num; i++)
                {
                    if (ValueList[i].flag == -1)
                        printf("The value of the variable %3d is 0\n", i);
                    else
                        printf("The value of the variable %3d is 1\n", i);
                }
            }
            // Save the result into the file
            if (ans[1] != INFEASIBLE)
            {
                strcpy(RFileName, LFileName);
                RFileName[strlen(RFileName) - 1] = 's';
                RFileName[strlen(RFileName) - 2] = 'e';
                RFileName[strlen(RFileName) - 3] = 'r';
                SaveResult(RFileName, state, t4);
            }
            getchar();
            getchar();
            break;
        case 7:
            reg = JudgeResult(RFileName);
            if (RFileName[strlen(RFileName) - 3] != 'r')
                printf("File is Empty!");
            else if (reg == OK)
                printf("\nRight!\n");
            else if (reg == ERROR)
                printf("\nERROR!\n");
            else
                printf("\nUnsatisfied or Timeout!\n");
            getchar();
            getchar();
            break;
        } // end of switch
    }     // end of while
}