#include <stdio.h>

/*������*/

const int N = 5; //��������������
int matrix[N][N] = {0}; //��ʾ����
int solution = 0;//��ĸ���
int count = 0; //�ڼ���
int move[8][2]={{-1,-2},{-2,-1}, {-2,1},{-1,2},{1,2},{2,1},{2,-1},{1,-2}};//�˸�����

//�����̷�Χ�ڣ����ҿɷ���
bool IsOK(int x, int y)
{
    if(( x <= N-1 ) && (x >=0 )
        && (y <= N-1 ) && (y >=0 )
        && (matrix[x ][y ]==0 ))
    {
        return true;
    }
    else
    {
        return false;
    }
}


//��ӡ�����н�
void Display()
{
    printf("��%d�ֽ⣺\n",++solution);
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            
            printf("%3d",matrix[i][j]);
        }
        printf("\n");
    }
    
    printf("-----------------\n");
}
void DFS(int x, int y)
{
    int nextX, nextY;


    for (int i = 0; i < 8; i++)
    {
        nextX = x + move[i][0];
        nextY = y + move[i][1];
        //--find
        if (IsOK(nextX, nextY))
        {
            
            if (count != N*N -1 )
            {
                //--forward
                count++;
                matrix[nextX][nextY] = count;
                
                DFS(nextX, nextY);
                matrix[nextX][nextY] = 0;
                count--;
            }
            else 
            {
                //--done
                Display();
            }
        }
    }
    //--back
}

int main()
{
    matrix[0][0] = 1;
    count = 1;
    DFS(0, 0);
    return 0;
}



