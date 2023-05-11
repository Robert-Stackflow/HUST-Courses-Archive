#include <stdio.h>
#include "../common/common.h"

#define RED	FB_COLOR(255,0,0)
#define ORANGE	FB_COLOR(255,165,0)
#define YELLOW	FB_COLOR(255,255,0)
#define GREEN	FB_COLOR(0,255,0)
#define CYAN	FB_COLOR(0,127,255)
#define BLUE	FB_COLOR(0,0,255)
#define PURPLE	FB_COLOR(139,0,255)
#define WHITE   FB_COLOR(255,255,255)
#define BLACK   FB_COLOR(0,0,0)

#define BLOCK_WIDTH 25
#define BOARD_WIDTH 500
#define BOARD_X ((SCREEN_WIDTH-BOARD_WIDTH)/2)
#define BOARD_Y ((SCREEN_HEIGHT-BOARD_WIDTH)/2)
#define BOARD_OFFSET 25

char board[15][15];

extern int gameState;
extern int playerColor;
extern int turnColor;
extern int winningColor;

void render()
{
    //background
    fb_draw_rect(0,0,SCREEN_WIDTH,SCREEN_HEIGHT,WHITE);
    //board
    fb_draw_rect(BOARD_X, BOARD_Y, BOARD_WIDTH, BOARD_WIDTH, ORANGE);
    //checker
    for(int i=0;i<15;i++)
    {
        for(int j=0;j<15;j++)
        {
            if(board[i][j] == 1)
            {
                fb_draw_circle(BOARD_X+BOARD_OFFSET+i*BLOCK_WIDTH, BOARD_Y+BOARD_OFFSET+j*BLOCK_WIDTH, 10, BLACK);
            }
            else if(board[i][j] == 2)
            {
                fb_draw_circle(BOARD_X+BOARD_OFFSET+i*BLOCK_WIDTH, BOARD_Y+BOARD_OFFSET+j*BLOCK_WIDTH, 10, WHITE);
            }
        }
    }
    //text
    if(playerColor == 1)
    {
        fb_draw_text(BOARD_X+BOARD_WIDTH+BOARD_OFFSET, 100, "你执黑", 32, BLACK);
    }
    else
    {
        fb_draw_text(BOARD_X+BOARD_WIDTH+BOARD_OFFSET, 100, "你执白", 32, BLACK);
    }
    if(turnColor == 1)
    {
        fb_draw_text(BOARD_X+BOARD_WIDTH+BOARD_OFFSET, 150, "黑方走棋", 32, BLACK);
    }
    else
    {
        fb_draw_text(BOARD_X+BOARD_WIDTH+BOARD_OFFSET, 150, "白方走棋", 32, BLACK);
    }
    //winning text
    if(!gameState)
    {
        if(winningColor == playerColor)
        {
            fb_draw_text(BOARD_X+BOARD_WIDTH+BOARD_OFFSET, 200, "你赢了！", 32, BLACK);
        }
        else
        {
            fb_draw_text(BOARD_X+BOARD_WIDTH+BOARD_OFFSET, 200, "你输了...", 32, BLACK);
        }
    }


	fb_update();
}