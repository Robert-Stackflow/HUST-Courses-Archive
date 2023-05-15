#include "cachelab.h"
#include <stdio.h>

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, k, tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7;
    if (M == 64 && N == 64)
    {
        for (i = 0; i < M / 8; i++)
        {
            for (j = 0; j < N / 8; j++)
            {
                for (k = 0; k < 4; k++)
                {
                    tmp0 = A[j * 8 + k][i * 8 + 0];
                    tmp1 = A[j * 8 + k][i * 8 + 1];
                    tmp2 = A[j * 8 + k][i * 8 + 2];
                    tmp3 = A[j * 8 + k][i * 8 + 3];
                    B[i * 8 + 0][j * 8 + k] = tmp0;
                    B[i * 8 + 1][j * 8 + k] = tmp1;
                    B[i * 8 + 2][j * 8 + k] = tmp2;
                    B[i * 8 + 3][j * 8 + k] = tmp3;
                }
                for (k = 0; k < 4; k++)
                {
                    tmp0 = A[j * 8 + k][i * 8 + 4 + 0];
                    tmp1 = A[j * 8 + k][i * 8 + 4 + 1];
                    tmp2 = A[j * 8 + k][i * 8 + 4 + 2];
                    tmp3 = A[j * 8 + k][i * 8 + 4 + 3];
                    B[i * 8 + 0][j * 8 + 4 + k] = tmp0;
                    B[i * 8 + 1][j * 8 + 4 + k] = tmp1;
                    B[i * 8 + 2][j * 8 + 4 + k] = tmp2;
                    B[i * 8 + 3][j * 8 + 4 + k] = tmp3;
                }
                for (k = 0; k < 4; k++)
                {
                    tmp0 = B[i * 8 + k][j * 8 + 4 + 0];
                    tmp1 = B[i * 8 + k][j * 8 + 4 + 1];
                    tmp2 = B[i * 8 + k][j * 8 + 4 + 2];
                    tmp3 = B[i * 8 + k][j * 8 + 4 + 3];
                    tmp4 = A[j * 8 + 4 + 0][i * 8 + k];
                    tmp5 = A[j * 8 + 4 + 1][i * 8 + k];
                    tmp6 = A[j * 8 + 4 + 2][i * 8 + k];
                    tmp7 = A[j * 8 + 4 + 3][i * 8 + k];
                    B[i * 8 + k][j * 8 + 4 + 0] = tmp4;
                    B[i * 8 + k][j * 8 + 4 + 1] = tmp5;
                    B[i * 8 + k][j * 8 + 4 + 2] = tmp6;
                    B[i * 8 + k][j * 8 + 4 + 3] = tmp7;
                    B[i * 8 + 4 + k][j * 8 + 0] = tmp0;
                    B[i * 8 + 4 + k][j * 8 + 1] = tmp1;
                    B[i * 8 + 4 + k][j * 8 + 2] = tmp2;
                    B[i * 8 + 4 + k][j * 8 + 3] = tmp3;
                }
                for (k = 0; k < 4; k++)
                {
                    tmp0 = A[j * 8 + 4 + k][i * 8 + 4 + 0];
                    tmp1 = A[j * 8 + 4 + k][i * 8 + 4 + 1];
                    tmp2 = A[j * 8 + 4 + k][i * 8 + 4 + 2];
                    tmp3 = A[j * 8 + 4 + k][i * 8 + 4 + 3];
                    B[i * 8 + 4 + 0][j * 8 + 4 + k] = tmp0;
                    B[i * 8 + 4 + 1][j * 8 + 4 + k] = tmp1;
                    B[i * 8 + 4 + 2][j * 8 + 4 + k] = tmp2;
                    B[i * 8 + 4 + 3][j * 8 + 4 + k] = tmp3;
                }
            }
        }
        for (i = 0; i < N; i++)
        {
            for (j = 8 * (M / 8); j < M; j++)
            {
                tmp0 = A[i][j];
                B[j][i] = tmp0;
            }
        }
        for (i = 8 * (N / 8); i < N; i++)
        {
            for (j = 0; j < 8 * (M / 8); j++)
            {
                tmp0 = A[i][j];
                B[j][i] = tmp0;
            }
        }
    }
    else
    {
        for (i = 0; i < M / 8; i++)
        {
            for (j = 0; j < N / 8; j++)
            {
                for (k = 0; k < 8; k++)
                {
                    tmp0 = A[j * 8 + k][i * 8 + 0];
                    tmp1 = A[j * 8 + k][i * 8 + 1];
                    tmp2 = A[j * 8 + k][i * 8 + 2];
                    tmp3 = A[j * 8 + k][i * 8 + 3];
                    tmp4 = A[j * 8 + k][i * 8 + 4];
                    tmp5 = A[j * 8 + k][i * 8 + 5];
                    tmp6 = A[j * 8 + k][i * 8 + 6];
                    tmp7 = A[j * 8 + k][i * 8 + 7];
                    B[i * 8 + 0][j * 8 + k] = tmp0;
                    B[i * 8 + 1][j * 8 + k] = tmp1;
                    B[i * 8 + 2][j * 8 + k] = tmp2;
                    B[i * 8 + 3][j * 8 + k] = tmp3;
                    B[i * 8 + 4][j * 8 + k] = tmp4;
                    B[i * 8 + 5][j * 8 + k] = tmp5;
                    B[i * 8 + 6][j * 8 + k] = tmp6;
                    B[i * 8 + 7][j * 8 + k] = tmp7;
                }
            }
        }
        for (i = 0; i < N; i++)
        {
            for (j = 8 * (M / 8); j < M; j++)
            {
                tmp0 = A[i][j];
                B[j][i] = tmp0;
            }
        }
        for (i = 8 * (N / 8); i < N; i++)
        {
            for (j = 0; j < 8 * (M / 8); j++)
            {
                tmp0 = A[i][j];
                B[j][i] = tmp0;
            }
        }
    }
}

// 简单的矩阵转置
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }
}

char trans_block_desc[] = "Use block as 8 * 8int";
void trans_block(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, k, w, tmp;
    int row = M / 8, rol = N / 8;
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < rol; j++)
        {
            for (k = 0; k < 8; k++)
            {
                for (w = 0; w < 8; w++)
                {
                    tmp = A[j * 8 + w][i * 8 + k];
                    B[i * 8 + k][j * 8 + w] = tmp;
                }
            }
        }
    }
    for (i = 0; i < N; i++)
    {
        for (j = 8 * (M / 8); j < M; j++)
        {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }
    for (i = 8 * (N / 8); i < N; i++)
    {
        for (j = 0; j < 8 * (M / 8); j++)
        {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }
}

char trans_block_8_desc[] = "Use block as 8 * 8int by 8 items in one time";
void trans_block_8(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, k, tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7;
    for (i = 0; i < M / 8; i++)
    {
        for (j = 0; j < N / 8; j++)
        {
            for (k = 0; k < 8; k++)
            {
                tmp0 = A[j * 8 + k][i * 8 + 0];
                tmp1 = A[j * 8 + k][i * 8 + 1];
                tmp2 = A[j * 8 + k][i * 8 + 2];
                tmp3 = A[j * 8 + k][i * 8 + 3];
                tmp4 = A[j * 8 + k][i * 8 + 4];
                tmp5 = A[j * 8 + k][i * 8 + 5];
                tmp6 = A[j * 8 + k][i * 8 + 6];
                tmp7 = A[j * 8 + k][i * 8 + 7];
                B[i * 8 + 0][j * 8 + k] = tmp0;
                B[i * 8 + 1][j * 8 + k] = tmp1;
                B[i * 8 + 2][j * 8 + k] = tmp2;
                B[i * 8 + 3][j * 8 + k] = tmp3;
                B[i * 8 + 4][j * 8 + k] = tmp4;
                B[i * 8 + 5][j * 8 + k] = tmp5;
                B[i * 8 + 6][j * 8 + k] = tmp6;
                B[i * 8 + 7][j * 8 + k] = tmp7;
            }
        }
    }
    for (i = 0; i < N; i++)
    {
        for (j = 8 * (M / 8); j < M; j++)
        {
            tmp0 = A[i][j];
            B[j][i] = tmp0;
        }
    }
    for (i = 8 * (N / 8); i < N; i++)
    {
        for (j = 0; j < 8 * (M / 8); j++)
        {
            tmp0 = A[i][j];
            B[j][i] = tmp0;
        }
    }
}

char trans_block_4_desc[] = "Use block as 4 * 4int by 4 items in one time";
void trans_block_4(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, k, tmp0, tmp1, tmp2, tmp3;
    for (i = 0; i < M / 4; i++)
    {
        for (j = 0; j < N / 4; j++)
        {
            for (k = 0; k < 4; k++)
            {
                tmp0 = A[j * 4 + k][i * 4 + 0];
                tmp1 = A[j * 4 + k][i * 4 + 1];
                tmp2 = A[j * 4 + k][i * 4 + 2];
                tmp3 = A[j * 4 + k][i * 4 + 3];

                B[i * 4 + 0][j * 4 + k] = tmp0;
                B[i * 4 + 1][j * 4 + k] = tmp1;
                B[i * 4 + 2][j * 4 + k] = tmp2;
                B[i * 4 + 3][j * 4 + k] = tmp3;
            }
        }
    }
    for (i = 0; i < N; i++)
    {
        for (j = 4 * (M / 4); j < M; j++)
        {
            tmp0 = A[i][j];
            B[j][i] = tmp0;
        }
    }
    for (i = 4 * (N / 4); i < N; i++)
    {
        for (j = 0; j < 4 * (M / 4); j++)
        {
            tmp0 = A[i][j];
            B[j][i] = tmp0;
        }
    }
}

void registerFunctions()
{
    registerTransFunction(transpose_submit, transpose_submit_desc);

    registerTransFunction(trans, trans_desc);

    registerTransFunction(trans_block, trans_block_desc);

    registerTransFunction(trans_block_8, trans_block_8_desc);

    registerTransFunction(trans_block_4, trans_block_4_desc);
}

// 检查B是否是A的转置
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; ++j)
        {
            if (A[i][j] != B[j][i])
            {
                return 0;
            }
        }
    }
    return 1;
}
