#include "../common/common.h"
#include <stdio.h>

#define COLOR_BACKGROUND FB_COLOR(0xff, 0xff, 0xff)
#define RED FB_COLOR(255, 0, 0)
#define ORANGE FB_COLOR(255, 165, 0)
#define YELLOW FB_COLOR(255, 255, 0)
#define GREEN FB_COLOR(0, 255, 0)
#define CYAN FB_COLOR(0, 127, 255)
#define BLUE FB_COLOR(0, 0, 255)
#define PURPLE FB_COLOR(139, 0, 255)
#define WHITE FB_COLOR(255, 255, 255)
#define BLACK FB_COLOR(0, 0, 0)

static int touch_fd;
int rect_w = 120, rect_h = 45;
int x_old[5], y_old[5], isPressing[5], color[5];
static void init()
{
	fb_draw_rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, COLOR_BACKGROUND);
	// fb_draw_border(0, 0, rect_w, rect_h, BLACK);
	// fb_draw_text(10, 30, "清空画布", 20, RED);
	fb_draw_rect(SCREEN_WIDTH - rect_w, 0, rect_w, rect_h, BLUE);
	fb_draw_text(SCREEN_WIDTH - rect_w + 10, 30, "清除屏幕", 24, YELLOW);
	fb_update();
}
static void touch_event_cb(int fd)
{
	int type, x, y, finger;
	type = touch_read(fd, &x, &y, &finger);
	switch (type)
	{
	case TOUCH_PRESS:
		if (x >= SCREEN_WIDTH - rect_w && x <= SCREEN_WIDTH && y <= rect_h)
		{
			init();
			return;
		}
		x_old[finger] = x, y_old[finger] = y, isPressing[finger] = 1;
		break;
	case TOUCH_MOVE:
		if (isPressing[finger])
			fb_draw_line_weight(x_old[finger], y_old[finger], x, y, 5, color[finger]);
		x_old[finger] = x, y_old[finger] = y;
		break;
	case TOUCH_RELEASE:
		isPressing[finger] = 0;
		break;
	case TOUCH_ERROR:
		close(fd);
		task_delete_file(fd);
		break;
	default:
		return;
	}
	fb_update();
	return;
}

int main(int argc, char *argv[])
{
	color[0] = YELLOW;
	color[1] = CYAN;
	color[2] = RED;
	color[3] = GREEN;
	color[4] = ORANGE;
	fb_init("/dev/fb0");
	font_init("./font.ttc");
	init();
	//打开多点触摸设备文件, 返回文件fd
	touch_fd = touch_init("/dev/input/event2");
	//添加任务, 当touch_fd文件可读时, 会自动调用touch_event_cb函数
	task_add_file(touch_fd, touch_event_cb);
	task_loop(); //进入任务循环
	return 0;
}
