/**
 * 2012-8-22�޸�
 * ��spfa�㷨���
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE 101       /* ɢ��ֵ�ռ��С */
#define MAXWIDTH 256       /* ÿ������ַ����� */
#define MAXFEE  (~0)       /* ������޷�������Ϊ����� */

typedef struct _LN_NO {    /* �����������������Ͷ��� */
    int lsn;               /* ��������� line sn */
    struct _LN_NO *next;
} TLN_NO, *PLN_NO;

typedef struct _ST_NODE {  /* ����վ��Ϣ��������Ͷ��� */
    char *snm;             /* ����վ���� station name */
    struct _LN_NO *lnxt;   /* ��վ���ڵ��������֧�� */
    struct _ST_NODE *next;
} TSTTN, *PSTTN;

typedef struct _LINE {     /* ��������Ϣ�ṹ */
    int lno;               /* �����߱�� line number */
    char *lnm;             /* ���������� line name */
	int price;             /* ���߻����ߵ�Ʊ�� */
} TLINE, *PLINE;

TSTTN *lut[HASHSIZE]; /* ����վ��Ϣ���ұ� lookup table */
TLINE *line;          /* �����߶�̬���� */
int cnt;              /* ����������, �������ߡ����ߺ��������ʼ�ߡ��յ��� */
unsigned *adj, *dst;  /* ��̬����, adj: �ڽӾ���, dst: ���·������ֵ */
unsigned *pth, *quu;  /* ��̬����, pth: ·��, quu: ���� */
int q_h, q_t;         /* ����quu��ͷq_h�Ͷ�βq_tԪ�ص��±� */
char *flg;            /* ��̬����, ��Ƕ����Ƿ������� */

unsigned Hash(char *str);   /* ɢ�к�������һ���ַ���ɢ��Ϊһ���޷����� */
char *Trim(char s[]);       /* ɾ���ַ�����β�Ŀհ��ַ� */
int LineNum(char lname[]);  /* ������·���Ʋ�����·��� */
int AssignNum(int num1, int num2);  /* ��������·�������һ�����߱�� */
int Cover(int num1, int num2);      /* �ж������������Ƿ��໥���� */
void SPFA(int n);                   /* ��Դ���·�����㷨 */
void Route(int m);                  /* ���·�� */

int main()
{
    FILE *pfile;
    PLN_NO pln, pln1, pln2;        /* ��·��������ָ�� */
    PSTTN psttn, psttn1, psttn2;   /* վ��������ָ�� */
    char row[MAXWIDTH], str[MAXWIDTH];
    char str1[MAXWIDTH], str2[MAXWIDTH];
    char *pch;
    int i, len, price;
    int lsn = 0;       /* �������������, ���������鰴��ŷ��� */
    int num1, num2;
    int h, h1, h2;

    if ((pfile = fopen("price.txt", "r")) == NULL) {
        printf("Fail to open file: price.txt!\n");
        exit(-1);
    }
    while (fgets(row, MAXWIDTH, pfile) != NULL)  /* ����Ʊ�������ļ� */
        if (strlen(Trim(row)) != 0)
            cnt++;   /* �Ե�����·(�������ߺ�����)���� */
    fclose(pfile);

    cnt += 2;  /* ���������������������ʼ��·���յ���· */
    line = (PLINE)calloc(cnt, sizeof(TLINE));  /* Ϊ��̬���ݽṹ����洢�� */
    adj = (unsigned *)calloc(cnt * cnt, sizeof(unsigned));  /* �ڽӾ��� */
    dst = (unsigned *)calloc(cnt, sizeof(unsigned));  /* ���·����ֵ�� */
    quu = (unsigned *)calloc(cnt, sizeof(unsigned));  /* �㷨���õĶ��� */
    pth = (unsigned *)calloc(cnt, sizeof(unsigned));  /* ·�� */
    flg = (char *)calloc(cnt, sizeof(char));          /* ��Ƕ����Ƿ��ڶ����� */

    if ((pfile = fopen("stations.txt", "r")) == NULL) {
        printf("Fail to open file: station.txt!\n");
        exit(-1);
    }
    /* ��·����������վ�����ݵĶ��봦�� */
    while (fgets(row, MAXWIDTH, pfile) != NULL) {  /* ���ļ��ж�һ���ַ�����row */
        if ((pch=strtok(row, ":,")) == NULL)       /* ����·�������������pchָ�� */
            continue;   /* ���еĴ��� */

        strcpy(str, pch);
        if ((len = strlen(Trim(str))) == 0)    /* �հ��ַ��еĴ��� */
            continue;
        line[lsn].lnm = (char*)calloc(len+1, sizeof(char));  /* ���������洢�� */
        strcpy(line[lsn].lnm, str);   /* ������·�� */
        line[lsn].lno = lsn;          /* ���߱�ŵ�������� */

        while ((pch=strtok(NULL, ",")) != NULL) {  /* ����·�ϵ���վ�Ĵ��� */
            strcpy(str, pch);    /* վ������ */
            if ((len = strlen(Trim(str))) == 0)   /* �հ��ַ��� */
                continue;
            h = Hash(str);  /* ����վ����ɢ��ֵ */
            for (psttn=lut[h]; psttn!=NULL; psttn=psttn->next)  /* �ڲ��ұ��������õ���վ */
                if (strcmp(psttn->snm, str) == 0)  /* �ҵ�, ����psttnָ���վ�� */
                    break;
            if (psttn == NULL) {  /* δ�ҵ�, ���½���㣬������ұ� */
                psttn = (PSTTN)calloc(1, sizeof(TSTTN));  /* �½���� */
                psttn->snm = (char *)calloc(len+1, sizeof(char));  /* վ�����ƶ�̬�洢 */
                strcpy(psttn->snm, str);
                psttn->next = lut[h];  /* �Ժ���ȳ���ʽ������ұ�ĵ���վ���� */
                lut[h] = psttn;
            }
            pln1 = (PLN_NO)calloc(1, sizeof(TLN_NO));  /* ������·��Ž�� */
            pln1->lsn = lsn;  /* ���뱾վ���������ߵ���� */
            pln1->next = psttn->lnxt;  /* ���ý���Ժ���ȳ���ʽ������·���֧���� */
            psttn->lnxt = pln1;
            for (pln2=pln1->next; pln2!=NULL; pln2=pln2->next) {  /* ֧������������ */
                adj[lsn*cnt+pln2->lsn] = 1; /* �ڵ㣬��վ���ǻ���վ�������� */
                adj[pln2->lsn*cnt+lsn] = 1; /* �Ӿ���������� */            }
        }
        lsn++;  /* ��������ŵ���, ��ͬ */
    }
    fclose(pfile);

    if ((pfile = fopen("price.txt", "r")) == NULL) {
        printf("Fail to open file: price.txt!\n");
        exit(-1);
    }
    /* Ʊ�����ݵĶ��봦�� */
    while (fgets(row, MAXWIDTH, pfile) != NULL) {  /* �������ļ���һ���ַ�����row */
        if ((len=strlen(Trim(row))) == 0) {  /* ����ǿ���������һ�� */
            continue;
        }
        if (sscanf(row, "%s %d", str, &price) < 2)  /* ����������ȡ�������ͼ۸� */
            continue;  /* �������в����������ͼ۸�������һ�� */

        if ((pch = strchr(str, ',')) != NULL) {     /* ������·�Ĵ��� */
            line[lsn].lnm = (char *)calloc((strlen(str)+3), sizeof(char));
            line[lsn].lnm[0] = '(';  /* ������·���ı��棬�����һ��Բ���� */
            strcpy(line[lsn].lnm+1, str);
            strcat(line[lsn].lnm, ")");

            *pch = '\0';  /* ������·������������������ȡ */
            strcpy(str1, str);
            strcpy(str2, pch+1);

            if ((num1 = LineNum(str1)) < 0) {  /* ���������ߺţ�С��0��������������ͬ */
                printf("�۸��price.txt�е�����: %sδ֪.\n", str1);
                exit(-1);
            }
            if ((num2 = LineNum(str2)) < 0) {
                printf("�۸��price.txt�е�����: %sδ֪.\n", str2);
                exit(-1);
            }
            line[lsn].lno = AssignNum(num1, num2);  /* �������߱�Ų�������������� */
            line[lsn].price = price;

            for (i=0; i<lsn; i++)  /* ���������������ߵ��ڽӹ�ϵ */
                /* ����num1��num2�ڽ��Ҳ��뱾�����໥���ǵ�����Ϊ�ڽ� */
                adj[i*cnt+lsn] = adj[lsn*cnt+i]
                               = (adj[num1*cnt+i] || adj[num2*cnt+i])
                                 && !Cover(i, lsn);
            lsn++;
        }
        else {  /* ���ߵĴ��� */
            if ((num1 = LineNum(str)) < 0) {
                printf("�۸��price.txt�е�����: %sδ֪.\n", str);
                exit(-1);
            }
            line[num1].price = price;
        }
    }
    fclose(pfile);

    line[cnt-2].lno = cnt - 2;  /* �������ʼ����źͱ��Ϊcnt_ln-2 */
    line[cnt-2].price = 0;      /* ����Ϊ0, ��ͬ */
    line[cnt-1].lno = cnt - 1;  /* ������յ�����źͱ��Ϊcnt_ln-1 */
    line[cnt-1].price = 0;

    printf("������ʼվ�����յ�վ��(��ʼվ,�յ�վ)��ctrl+Z�˳���\n");
    while (gets(row) != NULL) { /* ������ʼվ�����յ�վ������������row */
        if ((pch=strchr(row, ',')) == NULL) {  /* ���δ�ð�Ƕ��ŷָ� */
            printf("�����ʽ������ʼվ�����յ�վ��֮���ð�Ƕ��ŷָ���\n");
            continue;
        }

        *pch = '\0';  /* ���д�row�з������ʼվ���յ�վ */
        strcpy(str1, row);      /* �ֱ����str1��str2 */
        strcpy(str2, pch+1);
        h1 = Hash(Trim(str1));  /* �ֱ����ɢ��ֵ */
        h2 = Hash(Trim(str2));
        for (psttn1=lut[h1]; psttn1!=NULL; psttn1=psttn1->next)
            if (strcmp(psttn1->snm, str1) == 0)  /* �ڲ��ұ�������ʼվ��� */
                break;
        if (psttn1 == NULL) {  /* δ�ҵ� */
            printf("���޴�վ: %s\n", str1);
            continue;
        }
        for (psttn2=lut[h2]; psttn2!=NULL; psttn2=psttn2->next)
            if (strcmp(psttn2->snm, str2) == 0)  /* �ڲ��ұ������յ�վ��� */
                break;
        if (psttn2 == NULL) {  /* û���ҵ� */
            printf("���޴�վ: %s\n", str2);
            continue;
        }

        for (i=0; i<cnt; i++) {  /* �Ƚ�������ʼ�ߺ��յ��ߵ��ڽӹ�ϵ���� */
            adj[(cnt-2)*cnt+i] = adj[i*cnt+cnt-2] = 0;
            adj[(cnt-1)*cnt+i] = adj[i*cnt+cnt-1] = 0;
        }
        /* ����������ʼ�ߺ��յ�����������·���ڽӹ�ϵ */
        for (pln=psttn1->lnxt; pln!=NULL; pln=pln->next)
            for (i=0; i<cnt; i++)
                if (Cover(i, pln->lsn))
                    adj[(cnt-2)*cnt+i] = adj[i*cnt+cnt-2] = 1;
        for (pln=psttn2->lnxt; pln!=NULL; pln=pln->next)
            for (i=0; i<cnt; i++)
                if (Cover(i, pln->lsn))
                    adj[(cnt-1)*cnt+i] = adj[i*cnt+cnt-1] = 1;

        SPFA(cnt-2);  /* ��������ʼ��ΪԴ��, ������������·�� */
        if (dst[cnt-1] < MAXFEE) {  /* �������յ��ߴ���ͨ· */
            Route(pth[cnt-1]);      /* ���������·�� */
            printf(" = %u\n\n", dst[cnt-1]);  /* ������·��(��С����) */
        }
        else  /* ������ͨ· */
            printf("Can't reach!\n\n");

        printf("������ʼվ�����յ�վ��(��ʼվ,�յ�վ)��ctrl+Z�˳���\n");
    }

    return 0;
}

unsigned Hash(char *str)  /* ���ַ�������ɢ��ֵ */
{
    unsigned sum;

    for (sum=0; *str; str++)
        sum = sum * 31 + *str;

    return sum % HASHSIZE;
}

char *Trim(char s[])  /* ɾ���ַ�����β�հ��ַ� */
{
	int i, j, k;

	for (j=0; s[j]==' '||s[j]=='\t'||s[j]=='\n'||s[j]=='\r'; j++)
		;
	for (k=strlen(s)-1; s[k]==' '||s[k]=='\t'||s[k]=='\n'||s[k]=='\r'; k--)
		;
	for (i=j; i<=k; i++)
		s[i-j] = s[i];
	s[i-j] = '\0';

	return s;
}

int LineNum(char lname[])  /* ������·���Ʋ�����·��� */
{
    int i;

    for (i=0; i<cnt; i++)
        if (strcmp(line[i].lnm, lname) == 0)
            return i;

    return -1;  /* ��·��������ʱ����-1 */
}

int AssignNum(int num1, int num2)  /* �������߱���������߱�� */
{
    if (num1 == num2)
        return num1;
    if (num1 < num2) {  /* ����num1��num2��ֵ */
        num1 ^= num2;   /* ȷ��num1 > num2 */
        num2 ^= num1;
        num1 ^= num2;
    }
    return num1 * cnt + num2;
}

int Cover(int num1, int num2)  /* �ж��������Ƿ�����໥���� */
{
    int num11 = line[num1].lno / cnt;
    int num12 = line[num1].lno % cnt;
    int num21 = line[num2].lno / cnt;
    int num22 = line[num2].lno % cnt;

    if (num11 == 0)
        if (num21 == 0)
            return num12 == num22;
        else
            return num12 == num21 || num12 == num22;
    else if (num21 == 0)
        return num11 == num22 || num12 == num22;
    else
        return num11 == num21 || num11 == num22 ||
               num12 == num21 || num12 == num22;
}

void SPFA(int n)  /* ���·�����㷨, Դ��Ϊn */
{
    int i;

    memset(dst, MAXFEE, cnt * sizeof(unsigned));
    dst[n] = 0;      /* ��ʼ��, ��Դ��·��Ϊ0��������·����ֵΪ����� */
    quu[q_h=0] = n;  /* ��ʼ״̬�¶�����ֻ��Դ��n */
    q_t = 1;         /* ���г�ʼ��, ��ͷΪ0����βΪ1 */
    memset(flg, 0, cnt * sizeof(char));  /* ��ʼ����־ */
    flg[n] = 1;      /* ��ʾԴ��n�ڶ����� */

    while (q_h != q_t) {       /* ��ͷ�Ͷ�β�غ�ʱ�����㷨 */
        for (i=0; i<cnt; i++)  /* �ö�ͷ���Ż������ڽ�ÿ�����·����ֵ */
            if (adj[quu[q_h]*cnt+i] && dst[quu[q_h]]+line[i].price<dst[i]) {
            /* ����i���ͷ���ڽ���·����ֵ���ڶ�ͷ��·����ֵ�������ĺ� */
                dst[i] = dst[quu[q_h]]+line[i].price;  /* �Ż���i��·����ֵ */
                pth[i] = quu[q_h];  /* ����ͷ����Ϊ��i���Ż������·������ */
                if (!flg[i]) {      /* �����i���ڶ����� */
                    flg[i] = 1;     /* ����i���Ϊ�ڶ����� */
                    quu[q_t] = i;   /* ����i������� */
                    q_t = (q_t + 1) % cnt;  /* �޸Ķ�β */
                }
            }
        flg[quu[q_h]] = 0;      /* ��Ƕ�ͷ�㲻�ڶ����� */
        q_h = (q_h + 1) % cnt;  /* ��ͷ������� */
    }
}

void Route(int m)  /* �õݹ�������·�� */
{
    if (m == cnt - 2)
        return;
    Route(pth[m]);
    printf("-%s", line[m].lnm);
}
