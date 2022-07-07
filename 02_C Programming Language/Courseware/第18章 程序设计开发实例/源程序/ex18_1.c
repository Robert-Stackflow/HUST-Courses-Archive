/**
 * 2012-8-22修改
 * 用spfa算法求解
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE 101       /* 散列值空间大小 */
#define MAXWIDTH 256       /* 每行最大字符个数 */
#define MAXFEE  (~0)       /* 用最大无符号数作为无穷大 */

typedef struct _LN_NO {    /* 地铁线序号链结点类型定义 */
    int lsn;               /* 地铁线序号 line sn */
    struct _LN_NO *next;
} TLN_NO, *PLN_NO;

typedef struct _ST_NODE {  /* 地铁站信息链结点类型定义 */
    char *snm;             /* 地铁站名称 station name */
    struct _LN_NO *lnxt;   /* 该站所在地铁线序号支链 */
    struct _ST_NODE *next;
} TSTTN, *PSTTN;

typedef struct _LINE {     /* 地铁线信息结构 */
    int lno;               /* 地铁线编号 line number */
    char *lnm;             /* 地铁线名称 line name */
	int price;             /* 单线或联线的票价 */
} TLINE, *PLINE;

TSTTN *lut[HASHSIZE]; /* 地铁站信息查找表 lookup table */
TLINE *line;          /* 地铁线动态数组 */
int cnt;              /* 地铁线总数, 包括单线、联线和虚拟的起始线、终到线 */
unsigned *adj, *dst;  /* 动态数组, adj: 邻接矩阵, dst: 最短路径估计值 */
unsigned *pth, *quu;  /* 动态数组, pth: 路径, quu: 队列 */
int q_h, q_t;         /* 队列quu队头q_h和队尾q_t元素的下标 */
char *flg;            /* 动态数组, 标记顶点是否进入队列 */

unsigned Hash(char *str);   /* 散列函数，将一个字符串散列为一个无符号数 */
char *Trim(char s[]);       /* 删除字符串首尾的空白字符 */
int LineNum(char lname[]);  /* 根据线路名称查找线路序号 */
int AssignNum(int num1, int num2);  /* 由两条线路编号生成一个联线编号 */
int Cover(int num1, int num2);      /* 判断两条地铁线是否相互覆盖 */
void SPFA(int n);                   /* 单源最短路快速算法 */
void Route(int m);                  /* 输出路径 */

int main()
{
    FILE *pfile;
    PLN_NO pln, pln1, pln2;        /* 线路序号链结点指针 */
    PSTTN psttn, psttn1, psttn2;   /* 站点链表结点指针 */
    char row[MAXWIDTH], str[MAXWIDTH];
    char str1[MAXWIDTH], str2[MAXWIDTH];
    char *pch;
    int i, len, price;
    int lsn = 0;       /* 用作地铁线序号, 地铁线数组按序号访问 */
    int num1, num2;
    int h, h1, h2;

    if ((pfile = fopen("price.txt", "r")) == NULL) {
        printf("Fail to open file: price.txt!\n");
        exit(-1);
    }
    while (fgets(row, MAXWIDTH, pfile) != NULL)  /* 搜索票价数据文件 */
        if (strlen(Trim(row)) != 0)
            cnt++;   /* 对地铁线路(包括单线和联线)计数 */
    fclose(pfile);

    cnt += 2;  /* 计数器还需算上虚拟的起始线路和终到线路 */
    line = (PLINE)calloc(cnt, sizeof(TLINE));  /* 为动态数据结构申请存储区 */
    adj = (unsigned *)calloc(cnt * cnt, sizeof(unsigned));  /* 邻接矩阵 */
    dst = (unsigned *)calloc(cnt, sizeof(unsigned));  /* 最短路径估值表 */
    quu = (unsigned *)calloc(cnt, sizeof(unsigned));  /* 算法所用的队列 */
    pth = (unsigned *)calloc(cnt, sizeof(unsigned));  /* 路径 */
    flg = (char *)calloc(cnt, sizeof(char));          /* 标记顶点是否在队列中 */

    if ((pfile = fopen("stations.txt", "r")) == NULL) {
        printf("Fail to open file: station.txt!\n");
        exit(-1);
    }
    /* 线路名及其下属站名数据的读入处理 */
    while (fgets(row, MAXWIDTH, pfile) != NULL) {  /* 从文件中读一行字符串到row */
        if ((pch=strtok(row, ":,")) == NULL)       /* 将线路名分离出来，用pch指向 */
            continue;   /* 空行的处理 */

        strcpy(str, pch);
        if ((len = strlen(Trim(str))) == 0)    /* 空白字符行的处理 */
            continue;
        line[lsn].lnm = (char*)calloc(len+1, sizeof(char));  /* 申请线名存储区 */
        strcpy(line[lsn].lnm, str);   /* 存入线路名 */
        line[lsn].lno = lsn;          /* 单线编号等于其序号 */

        while ((pch=strtok(NULL, ",")) != NULL) {  /* 该线路上地铁站的处理 */
            strcpy(str, pch);    /* 站点名称 */
            if ((len = strlen(Trim(str))) == 0)   /* 空白字符串 */
                continue;
            h = Hash(str);  /* 计算站名的散列值 */
            for (psttn=lut[h]; psttn!=NULL; psttn=psttn->next)  /* 在查找表中搜索该地铁站 */
                if (strcmp(psttn->snm, str) == 0)  /* 找到, 则用psttn指向该站点 */
                    break;
            if (psttn == NULL) {  /* 未找到, 则新建结点，加入查找表 */
                psttn = (PSTTN)calloc(1, sizeof(TSTTN));  /* 新建结点 */
                psttn->snm = (char *)calloc(len+1, sizeof(char));  /* 站点名称动态存储 */
                strcpy(psttn->snm, str);
                psttn->next = lut[h];  /* 以后进先出方式插入查找表的地铁站链表 */
                lut[h] = psttn;
            }
            pln1 = (PLN_NO)calloc(1, sizeof(TLN_NO));  /* 建立线路序号结点 */
            pln1->lsn = lsn;  /* 存入本站所属地铁线的序号 */
            pln1->next = psttn->lnxt;  /* 将该结点以后进先出方式挂在线路编号支链上 */
            psttn->lnxt = pln1;
            for (pln2=pln1->next; pln2!=NULL; pln2=pln2->next) {  /* 支链上若有其他 */
                adj[lsn*cnt+pln2->lsn] = 1; /* 节点，则本站点是换乘站，需在邻 */
                adj[pln2->lsn*cnt+lsn] = 1; /* 接矩阵上做标记 */            }
        }
        lsn++;  /* 地铁线序号递增, 下同 */
    }
    fclose(pfile);

    if ((pfile = fopen("price.txt", "r")) == NULL) {
        printf("Fail to open file: price.txt!\n");
        exit(-1);
    }
    /* 票价数据的读入处理 */
    while (fgets(row, MAXWIDTH, pfile) != NULL) {  /* 从数据文件读一行字符串到row */
        if ((len=strlen(Trim(row))) == 0) {  /* 如果是空行则处理下一行 */
            continue;
        }
        if (sscanf(row, "%s %d", str, &price) < 2)  /* 从输入行中取出线名和价格 */
            continue;  /* 输入行中不包含线名和价格，则处理下一行 */

        if ((pch = strchr(str, ',')) != NULL) {     /* 联合线路的处理 */
            line[lsn].lnm = (char *)calloc((strlen(str)+3), sizeof(char));
            line[lsn].lnm[0] = '(';  /* 联合线路名的保存，外加了一对圆括号 */
            strcpy(line[lsn].lnm+1, str);
            strcat(line[lsn].lnm, ")");

            *pch = '\0';  /* 联合线路名中两条单线名的提取 */
            strcpy(str1, str);
            strcpy(str2, pch+1);

            if ((num1 = LineNum(str1)) < 0) {  /* 按线名找线号，小于0，则数据有误，下同 */
                printf("价格表price.txt中地铁线: %s未知.\n", str1);
                exit(-1);
            }
            if ((num2 = LineNum(str2)) < 0) {
                printf("价格表price.txt中地铁线: %s未知.\n", str2);
                exit(-1);
            }
            line[lsn].lno = AssignNum(num1, num2);  /* 生成联线编号并存入地铁线数组 */
            line[lsn].price = price;

            for (i=0; i<lsn; i++)  /* 联线与其他地铁线的邻接关系 */
                /* 将与num1和num2邻接且不与本联线相互覆盖的线置为邻接 */
                adj[i*cnt+lsn] = adj[lsn*cnt+i]
                               = (adj[num1*cnt+i] || adj[num2*cnt+i])
                                 && !Cover(i, lsn);
            lsn++;
        }
        else {  /* 单线的处理 */
            if ((num1 = LineNum(str)) < 0) {
                printf("价格表price.txt中地铁线: %s未知.\n", str);
                exit(-1);
            }
            line[num1].price = price;
        }
    }
    fclose(pfile);

    line[cnt-2].lno = cnt - 2;  /* 虚拟的起始线序号和编号为cnt_ln-2 */
    line[cnt-2].price = 0;      /* 费用为0, 下同 */
    line[cnt-1].lno = cnt - 1;  /* 虚拟的终到线序号和编号为cnt_ln-1 */
    line[cnt-1].price = 0;

    printf("输入起始站名和终到站名(起始站,终到站)，ctrl+Z退出：\n");
    while (gets(row) != NULL) { /* 输入起始站名和终到站名，存入数组row */
        if ((pch=strchr(row, ',')) == NULL) {  /* 如果未用半角逗号分隔 */
            printf("输入格式有误，起始站名和终到站名之间用半角逗号分隔！\n");
            continue;
        }

        *pch = '\0';  /* 从行串row中分离出起始站和终到站 */
        strcpy(str1, row);      /* 分别存入str1和str2 */
        strcpy(str2, pch+1);
        h1 = Hash(Trim(str1));  /* 分别计算散列值 */
        h2 = Hash(Trim(str2));
        for (psttn1=lut[h1]; psttn1!=NULL; psttn1=psttn1->next)
            if (strcmp(psttn1->snm, str1) == 0)  /* 在查找表中找起始站结点 */
                break;
        if (psttn1 == NULL) {  /* 未找到 */
            printf("查无此站: %s\n", str1);
            continue;
        }
        for (psttn2=lut[h2]; psttn2!=NULL; psttn2=psttn2->next)
            if (strcmp(psttn2->snm, str2) == 0)  /* 在查找表中找终到站结点 */
                break;
        if (psttn2 == NULL) {  /* 没有找到 */
            printf("查无此站: %s\n", str2);
            continue;
        }

        for (i=0; i<cnt; i++) {  /* 先将虚拟起始线和终到线的邻接关系置零 */
            adj[(cnt-2)*cnt+i] = adj[i*cnt+cnt-2] = 0;
            adj[(cnt-1)*cnt+i] = adj[i*cnt+cnt-1] = 0;
        }
        /* 建立虚拟起始线和终到线与其他线路的邻接关系 */
        for (pln=psttn1->lnxt; pln!=NULL; pln=pln->next)
            for (i=0; i<cnt; i++)
                if (Cover(i, pln->lsn))
                    adj[(cnt-2)*cnt+i] = adj[i*cnt+cnt-2] = 1;
        for (pln=psttn2->lnxt; pln!=NULL; pln=pln->next)
            for (i=0; i<cnt; i++)
                if (Cover(i, pln->lsn))
                    adj[(cnt-1)*cnt+i] = adj[i*cnt+cnt-1] = 1;

        SPFA(cnt-2);  /* 以虚拟起始线为源点, 求到其他点的最短路径 */
        if (dst[cnt-1] < MAXFEE) {  /* 到虚拟终到线存在通路 */
            Route(pth[cnt-1]);      /* 输出经过的路径 */
            printf(" = %u\n\n", dst[cnt-1]);  /* 输出最短路径(最小费用) */
        }
        else  /* 不存在通路 */
            printf("Can't reach!\n\n");

        printf("输入起始站名和终到站名(起始站,终到站)，ctrl+Z退出：\n");
    }

    return 0;
}

unsigned Hash(char *str)  /* 由字符串生成散列值 */
{
    unsigned sum;

    for (sum=0; *str; str++)
        sum = sum * 31 + *str;

    return sum % HASHSIZE;
}

char *Trim(char s[])  /* 删除字符串首尾空白字符 */
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

int LineNum(char lname[])  /* 根据线路名称查找线路序号 */
{
    int i;

    for (i=0; i<cnt; i++)
        if (strcmp(line[i].lnm, lname) == 0)
            return i;

    return -1;  /* 线路名不存在时返回-1 */
}

int AssignNum(int num1, int num2)  /* 由两单线编号生成联线编号 */
{
    if (num1 == num2)
        return num1;
    if (num1 < num2) {  /* 交换num1和num2的值 */
        num1 ^= num2;   /* 确保num1 > num2 */
        num2 ^= num1;
        num1 ^= num2;
    }
    return num1 * cnt + num2;
}

int Cover(int num1, int num2)  /* 判断两条线是否存在相互覆盖 */
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

void SPFA(int n)  /* 最短路快速算法, 源点为n */
{
    int i;

    memset(dst, MAXFEE, cnt * sizeof(unsigned));
    dst[n] = 0;      /* 初始化, 除源点路径为0外其他点路径估值为无穷大 */
    quu[q_h=0] = n;  /* 初始状态下队列中只有源点n */
    q_t = 1;         /* 队列初始化, 队头为0，队尾为1 */
    memset(flg, 0, cnt * sizeof(char));  /* 初始化标志 */
    flg[n] = 1;      /* 表示源点n在队列中 */

    while (q_h != q_t) {       /* 队头和队尾重合时结束算法 */
        for (i=0; i<cnt; i++)  /* 用队头点优化与其邻接每个点的路径估值 */
            if (adj[quu[q_h]*cnt+i] && dst[quu[q_h]]+line[i].price<dst[i]) {
            /* 若点i与队头点邻接且路径估值大于队头点路径估值与其距离的和 */
                dst[i] = dst[quu[q_h]]+line[i].price;  /* 优化点i的路径估值 */
                pth[i] = quu[q_h];  /* 将队头点作为点i的优化点存入路径数组 */
                if (!flg[i]) {      /* 如果点i不在队列中 */
                    flg[i] = 1;     /* 将点i标记为在队列中 */
                    quu[q_t] = i;   /* 将点i加入队列 */
                    q_t = (q_t + 1) % cnt;  /* 修改队尾 */
                }
            }
        flg[quu[q_h]] = 0;      /* 标记队头点不在队列中 */
        q_h = (q_h + 1) % cnt;  /* 队头点出队列 */
    }
}

void Route(int m)  /* 用递归调用输出路径 */
{
    if (m == cnt - 2)
        return;
    Route(pth[m]);
    printf("-%s", line[m].lnm);
}
