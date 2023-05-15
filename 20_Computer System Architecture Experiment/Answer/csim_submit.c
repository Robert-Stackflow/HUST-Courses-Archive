/*
 *csim.c-使用C编写一个Cache模拟器，它可以处理来自Valgrind的跟踪和输出统计
 *息，如命中、未命中和逐出的次数。更换政策是LRU。
 * 设计和假设:
 *  1. 每个加载/存储最多可导致一个缓存未命中。（最大请求是8个字节。）
 *  2. 忽略指令负载（I），因为我们有兴趣评估trace.c内容中数据存储性能。
 *  3. 数据修改（M）被视为加载，然后存储到同一地址。因此，M操作可能导致两次缓存命中，或者一次未命中和一次命中，外加一次可能的逐出。
 * 使用函数printSummary() 打印输出，输出hits, misses and evictions 的数，这对结果评估很重要
 */

#include "cachelab.h"
#include <assert.h>
#include <errno.h>
#include <getopt.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef unsigned long long int mem_addr_t;

typedef struct cache_line
{
    char valid;
    mem_addr_t tag;
    unsigned long long int lru;
} cache_line_t;                        /* cache行 */
typedef cache_line_t *cache_pointer_t; /* cache组指针 */
typedef cache_pointer_t *cache_t;      /* cache */

int v = 0;               /* 是否输出debug信息 */
int s = 0;               /* 组索引位数 */
int S;                   /* 组数 */
int b = 0;               /* 块内偏移位数 */
int B;                   /* 块大小,以字节为单位 */
int E = 0;               /* 相联度 */
char *trace_file = NULL; /* 访问轨迹文件地址 */

int miss_count = 0;                     /* 不命中次数 */
int hit_count = 0;                      /* 命中次数 */
int eviction_count = 0;                 /* 淘汰次数 */
unsigned long long int lru_counter = 1; /* LRU计数器，表示访问次数，则cache中LRU计数器越小，则表明越久未访问 */

cache_t cache; /* cache文件 */
mem_addr_t set_index_mask;

// 初始化cache
void initCache(int S, int E, int B)
{
    // 初始化cache，共S个组
    cache = (cache_pointer_t *)malloc(sizeof(cache_pointer_t) * S);
    // 初始化每个组
    for (int i = 0; i < S; i++)
    {
        // 每个组共E行
        cache_pointer_t cache_set = (cache_line_t *)malloc(sizeof(cache_line_t) * E);
        cache[i] = cache_set;
        // 初始化每个cache行
        for (int j = 0; j < E; j++)
        {
            cache_set[j].valid = 0;
            cache_set[j].tag = 0;
            cache_set[j].lru = 0;
        }
    }
    // 定义掩码，可用于得到内存地址中的索引部分
    set_index_mask = (mem_addr_t)((1 << s) - 1);
}

// 释放cache
void freeCache()
{
    for (int i = 0; i < E; i++)
    {
        free(cache[i]);
    }
    free(*cache);
}

// 根据addr访问cache
void accessData(mem_addr_t addr)
{
    // 得到组索引
    mem_addr_t set_index = (addr >> b) & set_index_mask;
    // 将地址右移s+b位得到标识
    mem_addr_t tag = addr >> (s + b);
    unsigned long long int eviction_lru = ULONG_MAX;
    int flag = 0;
    cache_pointer_t cache_set = cache[set_index];

    int eviction_line = 0;
    // 查找所在组，如果标识相等且valid则表示命中，并且该cache行的LRU计数器加1
    for (int i = 0; i < E; i++)
    {
        if ((cache_set[i].tag == tag) && (cache_set[i].valid == 1))
        {
            flag = 1;
            cache_set[i].lru = lru_counter++;
            break;
        }
    }
    if (flag)
    {
        // 如果命中，则命中次数加1
        hit_count++;
        if (v == 1)
            printf("hit ");
    }
    else
    {
        // 如果不命中，则不命中次数加1
        miss_count++;
        if (v == 1)
            printf("miss ");
        // 遍历所在组，找到第一个空闲cache行（valid为0）存入addr信息
        for (int i = 0; i < E; i++)
        {
            if (cache_set[i].valid == 0)
            {
                cache_set[i].valid = 1;
                cache_set[i].tag = tag;
                cache_set[i].lru = lru_counter++;
                flag = 1;
                break;
            }
        }
        // 如果不存在空闲cache行，则应淘汰
        if (flag == 0)
        {
            if (v == 1)
                printf("eviction ");
            // 查找cache行，找到LRU计数器值最小的cache行淘汰
            for (int i = 0; i < E; i++)
            {
                if (cache_set[i].lru < eviction_lru)
                {
                    eviction_line = i;
                    eviction_lru = cache_set[i].lru;
                }
            }
            // 淘汰次数加1
            eviction_count++;
            // 存入addr信息
            cache_set[eviction_line].valid = 1;
            cache_set[eviction_line].tag = tag;
            cache_set[eviction_line].lru = lru_counter++;
        }
    }
}

void replayTrace(char *trace_fn)
{
    char buf[1000];
    mem_addr_t addr = 0;
    unsigned int len = 0;
    FILE *trace_fp = fopen(trace_fn, "r");

    if (!trace_fp)
    {
        fprintf(stderr, "%s: %s\n", trace_fn, strerror(errno));
        exit(1);
    }
    // 打开访问轨迹文件并读取至buf中
    while (fgets(buf, 1000, trace_fp) != NULL)
    {
        if (buf[1] == 'S' || buf[1] == 'L' || buf[1] == 'M')
        {
            sscanf(buf + 3, "%llx,%u", &addr, &len);
            if (v)
                printf("%c %llx,%u ", buf[1], addr, len);
            accessData(addr);

            if (buf[1] == 'M')
                accessData(addr);
            if (v)
                printf("\n");
        }
    }

    fclose(trace_fp);
}

void printUsage(char *argv[])
{
    printf("Usage: %s [-hv] -s <num> -E <num> -b <num> -t <file>\n", argv[0]);
    printf("Options:\n");
    printf("  -h         Print this help message.\n");
    printf("  -v         Optional verbose flag.\n");
    printf("  -s <num>   Number of set index bits.\n");
    printf("  -E <num>   Number of lines per set.\n");
    printf("  -b <num>   Number of block offset bits.\n");
    printf("  -t <file>  Trace file.\n");
    printf("\nExamples:\n");
    printf("  linux>  %s -s 4 -E 1 -b 4 -t traces/yi.trace\n", argv[0]);
    printf("  linux>  %s -v -s 8 -E 2 -b 4 -t traces/yi.trace\n", argv[0]);
    exit(0);
}

int main(int argc, char *argv[])
{
    char c;
    while ((c = getopt(argc, argv, "s:E:b:t:vh")) != -1)
    {
        switch (c)
        {
        case 's':
            s = atoi(optarg);
            break;
        case 'E':
            E = atoi(optarg);
            break;
        case 'b':
            b = atoi(optarg);
            break;
        case 't':
            trace_file = optarg;
            break;
        case 'v':
            v = 1;
            break;
        case 'h':
            printUsage(argv);
            exit(0);
        default:
            printUsage(argv);
            exit(1);
        }
    }

    if (s == 0 || E == 0 || b == 0 || trace_file == NULL)
    {
        printf("%s: Missing required command line argument\n", argv[0]);
        printUsage(argv);
        exit(1);
    }

    S = 1 << s;
    B = 1 << b;

    initCache(S, E, B);
    replayTrace(trace_file);
    // freeCache();
    printSummary(hit_count, miss_count, eviction_count);
    return 0;
}