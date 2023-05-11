#include <stdio.h>
#include "../common/common.h"

extern char board[15][15];
extern int gameState;
extern int playerColor;
extern int turnColor;
extern int winningColor;

void init()
{
	for(int i=0;i<15;i++)
	{
		for(int j=0;j<15;j++)
		{
			board[i][j] = 0;
		}
	}
    turnColor = 1;
    playerColor = 1;
    winningColor = 0;
    gameState = 1;
}

int checkEnd(int x, int y)
{
    return
    (
        //横
        (
            x >= 4 && board[x][y] == board[x-1][y] && board[x][y] == board[x-2][y]
            && board[x][y] == board[x-3][y] && board[x][y] == board[x-4][y]
        ) ||
        (
            x >= 3 && x <= 13 &&board[x][y] == board[x-1][y] && board[x][y] == board[x-2][y]
            && board[x][y] == board[x-3][y] && board[x][y] == board[x+1][y]
        ) ||
        (
            x >= 2 && x <= 12 &&board[x][y] == board[x-1][y] && board[x][y] == board[x-2][y]
            && board[x][y] == board[x+1][y] && board[x][y] == board[x+2][y]
        ) ||
        (
            x >= 1 && x <= 11 &&board[x][y] == board[x-1][y] && board[x][y] == board[x+1][y]
            && board[x][y] == board[x+2][y] && board[x][y] == board[x+3][y]
        ) ||
        (
            x <= 10 && board[x][y] == board[x+1][y] && board[x][y] == board[x+2][y]
            && board[x][y] == board[x+3][y] && board[x][y] == board[x+4][y]
        ) ||
        //纵
        (
            y >= 4 && board[x][y] == board[x][y-1] && board[x][y] == board[x][y-2]
            && board[x][y] == board[x][y-3] && board[x][y] == board[x][y-4]
        ) ||
        (
            y >= 3 && y <= 13 &&board[x][y] == board[x][y-1] && board[x][y] == board[x][y-2]
            && board[x][y] == board[x][y-3] && board[x][y] == board[x][y+1]
        ) ||
        (
            y >= 2 && y <= 12 &&board[x][y] == board[x][y-1] && board[x][y] == board[x][y-2]
            && board[x][y] == board[x][y+1] && board[x][y] == board[x][y+2]
        ) ||
        (
            y >= 1 && y <= 11 &&board[x][y] == board[x][y-1] && board[x][y] == board[x][y+1]
            && board[x][y] == board[x][y+2] && board[x][y] == board[x][y+3]
        ) ||
        (
            y <= 10 && board[x][y] == board[x][y+1] && board[x][y] == board[x][y+2]
            && board[x][y] == board[x][y+3] && board[x][y] == board[x][y+4]
        ) ||
        //正对角
        (
            x >= 4 && y >= 4 && board[x][y] == board[x-1][y-1] && board[x][y] == board[x-2][y-2]
            && board[x][y] == board[x-3][y-3] && board[x][y] == board[x-4][y-4]
        ) ||
        (
            x >= 3 && x <= 13 && y >= 3 && y <= 13 &&board[x][y] == board[x-1][y-1] && board[x][y] == board[x-2][y-2]
            && board[x][y] == board[x-3][y-3] && board[x][y] == board[x+1][y+1]
        ) ||
        (
            x >= 2 && x <= 12 && y >= 2 && y <= 12 &&board[x][y] == board[x-1][y-1] && board[x][y] == board[x-2][y-2]
            && board[x][y] == board[x+1][y+1] && board[x][y] == board[x+2][y+2]
        ) ||
        (
            x >= 1 && x <= 11 && y >= 1 && y <= 11 &&board[x][y] == board[x-1][y-1] && board[x][y] == board[x+1][y+1]
            && board[x][y] == board[x+2][y+2] && board[x][y] == board[x+3][y+3]
        ) ||
        (
            x <= 10 && y <= 10&& board[x][y] == board[x+1][y+1] && board[x][y] == board[x+2][y+2]
            && board[x][y] == board[x+3][y+3] && board[x][y] == board[x+4][y+4]
        ) ||
        //反对角
        (
            x >= 4 && y <= 10 && board[x][y] == board[x-1][y+1] && board[x][y] == board[x-2][y+2]
            && board[x][y] == board[x-3][y+3] && board[x][y] == board[x-4][y+4]
        ) ||
        (
            x >= 3 && x <= 13 && y >= 1 && y <= 11 &&board[x][y] == board[x-1][y+1] && board[x][y] == board[x-2][y+2]
            && board[x][y] == board[x-3][y+3] && board[x][y] == board[x+1][y-1]
        ) ||
        (
            x >= 2 && x <= 12 && y >= 2 && y <= 12 &&board[x][y] == board[x-1][y+1] && board[x][y] == board[x-2][y+2]
            && board[x][y] == board[x+1][y-1] && board[x][y] == board[x+2][y-2]
        ) ||
        (
            x >= 1 && x <= 11 && y >= 3 && y <= 13 &&board[x][y] == board[x-1][y+1] && board[x][y] == board[x+1][y-1]
            && board[x][y] == board[x+2][y-2] && board[x][y] == board[x+3][y-3]
        ) ||
        (
            x <= 10 && y >= 4 && board[x][y] == board[x+1][y-1] && board[x][y] == board[x+2][y-2]
            && board[x][y] == board[x+3][y-3] && board[x][y] == board[x+4][y-4]
        )
    );
}