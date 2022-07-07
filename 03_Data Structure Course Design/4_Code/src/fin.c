#include "fin.h"
int LoadFile(const char *FileName, CNF *cnf)
{
    FILE *fin = fopen(FileName, "r");
    if (!fin)
        return INFEASIBLE;
    char ch;
    int mid, acount = 0;
    while (fread(&ch, sizeof(char), 1, fin))
    {
        // read the content of the notes
        if (ch != 'p')
            continue;
        else
            break;
    }
    // BUG If the comment contains the letter p, it will cause an error
    if (ch == 'p')
    {
        // read the information of the data
        fgetc(fin);
        fscanf(fin, "%s%d%d", cnf->type, &cnf->literal_num, &cnf->clause_num);
        acount = cnf->clause_num;
        fgetc(fin);
    }
    ClauseNode *p = NULL, *t = NULL;
    HeadNode *q = NULL, *r = NULL, *head = NULL;
    head = (HeadNode *)malloc(sizeof(HeadNode));
    head->next = NULL;
    head->horizon = NULL;
    head->count = head->flag = 0;
    r = q = head;
    while (!feof(fin))
    {
        // read the clauses line by line
        while ((fscanf(fin, "%d", &mid)) != EOF && acount)
        {
            if (mid != 0)
            {
                // Read arguments
                p = (ClauseNode *)malloc(sizeof(ClauseNode));
                p->next = NULL;
                p->flag = 0;
                p->literal = mid;
                // Insert node
                if (q->horizon == NULL)
                    q->horizon = p;
                else
                {
                    t = q->horizon;
                    while (t->next)
                        t = t->next;
                    t->next = p;
                }
                // add the number of arguments
                q->count++;
            }
            else
            {
                // Read the next formula
                acount--;
                if (acount)
                {
                    r = (HeadNode *)malloc(sizeof(HeadNode));
                    r->next = NULL;
                    r->flag = 0;
                    r->horizon = NULL;
                    r->count = 0;
                    q->next = r;
                    q = r;
                }
            }
        }
        while (fread(&ch, sizeof(char), 1, fin))
        {
            // read the content of the notes
            if (ch != 'p')
                continue;
            else
                break;
        }
    }
    cnf->head = head;
    fclose(fin);
    return OK;
}

void DisplayCNF(CNF *cnf)
{
    ClauseNode *p = NULL;
    HeadNode *q = NULL;
    q = cnf->head;
    printf("The number of literals:%d\nThe number of clauses:%d\n", cnf->literal_num, cnf->clause_num);
    while (q)
    {
        printf("%3d: ", q->count);
        p = q->horizon;
        while (p)
        {
            printf("%6d ", p->literal);
            p = p->next;
        }
        printf("\n");
        q = q->next;
    }
}

int SaveCNF(const char *FileName, CNF *cnf)
{
    ClauseNode *p = NULL;
    HeadNode *q = NULL;
    FILE *fp;
    if ((fp = fopen(FileName, "wb")) == NULL)
    {
        return INFEASIBLE;
    }
    else
    {
        fprintf(fp, "%s", "p cnf ");
        fprintf(fp, "%d ", cnf->literal_num);
        fprintf(fp, "%d \n", cnf->clause_num);
        q = cnf->head;
        while (q)
        {
            p = q->horizon;
            while (p)
            {
                fprintf(fp, "%d ", p->literal);
                p = p->next;
            }
            fprintf(fp, "0\n");
            q = q->next;
        }
        fclose(fp);
    }
    return OK;
}

void DestoryCNF(CNF *cnf)
{
    ClauseNode *p = NULL, *r = NULL;
    HeadNode *q = NULL, *t = NULL;
    q = cnf->head;
    while (q)
    {
        p = q->horizon;
        while (p)
        {
            r = p->next;
            free(p);
            p = r;
        }
        q->horizon = NULL;
        q = q->next;
    }
    q = cnf->head;
    while (q)
    {
        t = q->next;
        free(q);
        q = t;
    }
    cnf->head = NULL;
    cnf->clause_num = cnf->literal_num = 0;
}