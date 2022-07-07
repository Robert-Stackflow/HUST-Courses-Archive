#include <stdio.h>
#include <stack>
using namespace std;

/*马走日*/

const int N = 5; //棋盘行数跟列数
int matrix[N][N] = {0}; //表示棋盘
int solution = 0;//解的个数
int count = 0; //第几步
int move[8][2]={{-1,-2},{-2,-1}, {-2,1},{-1,2},{1,2},{2,1},{2,-1},{1,-2}};//八个方向

//注意find这一步当前层的的结点，结点的坐标不是x与y，而通过Node中的x与y与direction三者计算后得到当前层的结点
struct Node
{
    int x;
    int y;
    int direction;
};

//在棋盘范围内，而且可放棋
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

//打印
void Print()
{
    printf("第%d种解：\n",++solution);
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
                //把ok的节点放到当前层
                stack.pop();
                stack.push(node);

                x = node.x + move[node.direction][0];
                y = node.y + move[node.direction][1];
                matrix[x][y] = count++;
                
                //进入下一层的第一个节点
                node.x = x;
                node.y = y;
                node.direction = 0;
                stack.push(node);
            }
            else
            {
                //--done
                //打印出结果;
                x = node.x + move[node.direction][0];
                y = node.y + move[node.direction][1];
                matrix[x][y] = count++;
                Print();
                //注意先清除当前结点的数据
                matrix[x][y] = 0;
                count--;
                //进入当前层的下一个结点;
                node.direction++;
                stack.pop();
                stack.push(node);
            }
        }
        else
        {

            //----back
            //返回上一层当前结点的下一个节点
            stack.pop();
            if (stack.size() == 1)
            {
                return;
            }
            node = stack.top();
            //注意先清除当前结点的数据
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

