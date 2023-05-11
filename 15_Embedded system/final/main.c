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

static int touch_fd;
static int bluetooth_fd;

int gameState = 1;
int playerColor;
int turnColor;
int winningColor;

extern char board[15][15];

void init();
void render();
int checkEnd(int x, int y);

static void touch_event_cb(int fd)
{
	int type,x,y,finger;
	int boardX, boardY;
	char buffer[40];
	type = touch_read(fd, &x,&y,&finger);
	switch(type){
	case TOUCH_PRESS:
		printf("TOUCH_PRESS：x=%d,y=%d,finger=%d\n",x,y,finger);
		break;
	case TOUCH_MOVE:
		printf("TOUCH_MOVE：x=%d,y=%d,finger=%d\n",x,y,finger);
		break;
	case TOUCH_RELEASE:
		printf("TOUCH_RELEASE：x=%d,y=%d,finger=%d\n",x,y,finger);
		if(gameState)
		{
			if(playerColor == turnColor)
			{
				boardX = (x+12-(BOARD_X+BOARD_OFFSET)) / 25;
				boardY = (y+12-(BOARD_Y+BOARD_OFFSET)) / 25;
				if(boardX >=0 && boardX <= 14 &&
				boardY >= 0 && boardY <= 14)
				{
					if(board[boardX][boardY] == 0)
					{
						//落子
						board[boardX][boardY] = playerColor;
						//蓝牙数据
						sprintf(buffer, "%d %d %d", boardX, boardY, playerColor);
						myWrite_nonblock(bluetooth_fd, buffer, 40);
						if(checkEnd(boardX, boardY))
						{
							winningColor = playerColor;
							gameState = 0;
						}
						turnColor = 3 - turnColor;
						render();
					}
				}
			}
		}
		break;
	case TOUCH_ERROR:
		printf("close touch fd\n");
		close(fd);
		task_delete_file(fd);
		break;
	default:
		return;
	}
	return;
}

static void bluetooth_tty_event_cb(int fd)
{
	char buf[128];
	int n;

	n = myRead_nonblock(fd, buf, sizeof(buf)-1);
	if(n <= 0) {
		printf("close bluetooth tty fd\n");
		//task_delete_file(fd);
		//close(fd);
		exit(0);
		return;
	}

	buf[n] = '\0';
	printf("bluetooth tty receive \"%s\"\n", buf);
	//落子
	int x, y, c;
	sscanf(buf, "%d%d%d", &x, &y, &c);
	//落子
	board[x][y] = c;
	//判断颜色
	if(playerColor == c)
	{
		playerColor = 3 - c;
	}
	if(checkEnd(x, y))
	{
		winningColor = c;
		gameState = 0;
	}
	turnColor = 3 - turnColor;
	render();
	return;
}

static int bluetooth_tty_init(const char *dev)
{
	int fd = open(dev, O_RDWR|O_NOCTTY|O_NONBLOCK); /*非阻塞模式*/
	if(fd < 0){
		printf("bluetooth_tty_init open %s error(%d): %s\n", dev, errno, strerror(errno));
		return -1;
	}
	return fd;
}

int main(int argc, char *argv[])
{
	fb_init("/dev/fb0");
	font_init("./font.ttc");

	init();

	//打开多点触摸设备文件, 返回文件fd
	touch_fd = touch_init("/dev/input/event2");
	//添加任务, 当touch_fd文件可读时, 会自动调用touch_event_cb函数
	task_add_file(touch_fd, touch_event_cb);

	bluetooth_fd = bluetooth_tty_init("/dev/rfcomm0");
	if(bluetooth_fd == -1) return 0;
	task_add_file(bluetooth_fd, bluetooth_tty_event_cb);

	task_loop(); //进入任务循环
	return 0;
}