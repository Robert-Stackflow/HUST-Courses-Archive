#include <stdio.h>
#include <stack>
using namespace std;

/*������*/

const int N = 5; //��������������
int matrix[N][N] = {0}; //��ʾ����
int solution = 0;//��ĸ���
int count = 0; //�ڼ���
int move[8][2]={{-1,-2},{-2,-1}, {-2,1},{-1,2},{1,2},{2,1},{2,-1},{1,-2}};//�˸�����

//ע��find��һ����ǰ��ĵĽ�㣬�������겻��x��y����ͨ��Node�е�x��y��direction���߼����õ���ǰ��Ľ��
struct Node
{
    int x;
    int y;
    int direction;
};

//�����̷�Χ�ڣ����ҿɷ���
bool IsOk(Node node)
{
    int x, y;
    x = node.x + move[node.direction][0];
    y = node.y + move[node.direction][1];
    if(( x <= N-1 ) && (x >=0 )
        && (y <= N-1 ) && (y >=0 )
        && (matrix[x][y]==0 ))
    {
        return true;
    }
    else
    {
        return false;
    }
}

//��ӡ
void Print()
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


void DFS()
{
    Node node;
    stack<Node> stack;
    int x, y;
    count = 1;
    node.x = 0;
    node.y = 0;
    node.direction = 0;
    matrix[0][0] = count++;
    stack.push(node);

    node.direction = 0;
    stack.push(node);
    
    while(stack.size() >= 2)
    {
        //--find
        node = stack.top();
        while (node.direction < 8 && !IsOk(node))
        {
            node.direction++;
        }
        if (node.direction < 8)
        {
            //--forward
            if (count < N * N)
            {
                //��ok�Ľڵ�ŵ���ǰ��
                stack.pop();
                stack.push(node);

                x = node.x + move[node.direction][0];
                y = node.y + move[node.direction][1];
                matrix[x][y] = count++;
                
                //������һ��ĵ�һ���ڵ�
                node.x = x;
                node.y = y;
                node.direction = 0;
                stack.push(node);
            }
            else
            {
                //--done
                //��ӡ�����;
                x = node.x + move[node.direction][0];
                y = node.y + move[node.direction][1];
                matrix[x][y] = count++;
                Print();
                //ע���������ǰ��������
                matrix[x][y] = 0;
                count--;
                //���뵱ǰ�����һ�����;
                node.direction++;
                stack.pop();
                stack.push(node);
            }
        }
        else
        {

            //----back
            //������һ�㵱ǰ������һ���ڵ�
            stack.pop();
            if (stack.size() == 1)
            {
                return;
            }
            node = stack.top();
            //ע���������ǰ��������
            x = node.x + move[node.direction][0];
            y = node.y + move[node.direction][1];
            matrix[x][y] = 0;
            count--;

            node.direction++;
            stack.pop();
            stack.push(node);
            
        }
    }
}


int main()
{
    DFS();
    return 0;
}

