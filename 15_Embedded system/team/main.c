#include "../common/common.h"
#include <stdio.h>

#define COLOR_BACKGROUND FB_COLOR(0xff, 0xff, 0xff)
#define COLOR_TEXT FB_COLOR(0x0, 0x0, 0x0)
#define COLOR_TEXT_GRAY FB_COLOR(0xad, 0x80, 0x97)

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
static int bluetooth_fd;

#define TIME_X (SCREEN_WIDTH - 364)
#define TIME_Y 2
#define TIME_W 120
#define TIME_H 40

#define COLOR_X (SCREEN_WIDTH - 364)
#define COLOR_Y 2
#define COLOR_W 120
#define COLOR_H 40

#define SEND_X (SCREEN_WIDTH - 242)
#define SEND_Y 2
#define SEND_W 120
#define SEND_H 40

#define CLEAR_X (SCREEN_WIDTH - 120)
#define CLEAR_Y 2
#define CLEAR_W 120
#define CLEAR_H 40

#define INC_X (SCREEN_WIDTH - 364)
#define INC_Y 44
#define INC_W 120
#define INC_H 40

#define CUR_X (SCREEN_WIDTH - 242)
#define CUR_Y 44
#define CUR_W 120
#define CUR_H 40

#define DEC_X (SCREEN_WIDTH - 120)
#define DEC_Y 44
#define DEC_W 120
#define DEC_H 40

#define MIN_WEIGHT 3
#define MAX_WEIGHT 20

int x_old[5], y_old[5], isPressing[5], color[5], weight = 5, colorIndex = 0;
int rec_x_old[5], rec_y_old[5], rec_isPressing[5], rec_color[5], rec_weight = 8, rec_colorIndex = 0;

static void init()
{
	fb_draw_rect(COLOR_X, COLOR_Y, 364, 82, COLOR_BACKGROUND);
	fb_draw_border(SEND_X, SEND_Y, SEND_W, SEND_H, COLOR_TEXT_GRAY);
	fb_draw_text(SEND_X + 12, SEND_Y + 30, "发送消息", 24, COLOR_TEXT_GRAY);
	fb_draw_border(CLEAR_X, CLEAR_Y, CLEAR_W, CLEAR_H, COLOR_TEXT);
	fb_draw_text(CLEAR_X + 12, CLEAR_Y + 30, "清除屏幕", 24, COLOR_TEXT);
	if (weight < MAX_WEIGHT)
	{
		fb_draw_border(INC_X, INC_Y, INC_W, INC_H, COLOR_TEXT);
		fb_draw_text(INC_X + 12, INC_Y + 30, "增大线宽", 24, COLOR_TEXT);
	}
	if (weight >= MAX_WEIGHT)
	{
		fb_draw_border(INC_X, INC_Y, INC_W, INC_H, COLOR_TEXT_GRAY);
		fb_draw_text(INC_X + 12, INC_Y + 30, "增大线宽", 24, COLOR_TEXT_GRAY);
	}
	if (weight > MIN_WEIGHT)
	{
		fb_draw_border(DEC_X, DEC_Y, DEC_W, DEC_H, COLOR_TEXT);
		fb_draw_text(DEC_X + 12, DEC_Y + 30, "减小线宽", 24, COLOR_TEXT);
	}
	if (weight <= MIN_WEIGHT)
	{
		fb_draw_border(DEC_X, DEC_Y, DEC_W, DEC_H, COLOR_TEXT_GRAY);
		fb_draw_text(DEC_X + 12, DEC_Y + 30, "减小线宽", 24, COLOR_TEXT_GRAY);
	}
	{
		char buf[50];
		sprintf(buf, "线宽为%d", weight);
		fb_draw_border(CUR_X, CUR_Y, CUR_W, CUR_H, COLOR_TEXT);
		fb_draw_text(CUR_X + 12, CUR_Y + 30, buf, 24, COLOR_TEXT);
		fb_draw_rect(COLOR_X, COLOR_Y, COLOR_W, COLOR_H, color[colorIndex]);
		fb_draw_border(COLOR_X, COLOR_Y, COLOR_W, COLOR_H, BLACK);
		fb_draw_text(COLOR_X + 12, COLOR_Y + 30, "画笔颜色", 24, COLOR_BACKGROUND);
	}
	fb_update();
}

static int getColor(int finger)
{
	return color[(finger + colorIndex) % 5];
}

static void touch_event_cb(int fd)
{
	char buf[80];
	int type, x, y, finger;
	type = touch_read(fd, &x, &y, &finger);
	sprintf(buf, "%d %d %d %d %d %d\n", type, x, y, finger, weight, getColor(finger));
	myWrite_nonblock(bluetooth_fd, buf, 80);
	switch (type)
	{
	case TOUCH_PRESS:
		x_old[finger] = x, y_old[finger] = y, isPressing[finger] = 1;
		{
			if ((x >= CLEAR_X) && (x < CLEAR_X + CLEAR_W) && (y >= CLEAR_Y) && (y < CLEAR_Y + CLEAR_H))
				fb_draw_rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, COLOR_BACKGROUND), init();
			if ((x >= INC_X) && (x < INC_X + INC_W) && (y >= INC_Y) && (y < INC_Y + INC_H))
			{
				if (weight < MAX_WEIGHT)
					weight++;
				init();
			}
			if ((x >= DEC_X) && (x < DEC_X + DEC_W) && (y >= DEC_Y) && (y < DEC_Y + DEC_H))
			{
				if (weight > MIN_WEIGHT)
					weight--;
				init();
			}
			if ((x >= COLOR_X) && (x < COLOR_X + COLOR_W) && (y >= COLOR_Y) && (y < COLOR_Y + COLOR_H))
				colorIndex = (colorIndex + 1) % 5, init();
		}
		break;
	case TOUCH_MOVE:
		if (isPressing[finger])
			fb_draw_line_weight(x_old[finger], y_old[finger], x, y, weight, getColor(finger));
		x_old[finger] = x, y_old[finger] = y;
		break;
	case TOUCH_RELEASE:
		isPressing[finger] = 0;
		break;
	case TOUCH_ERROR:
		task_delete_file(fd);
		close(fd);
		break;
	default:
		return;
	}
	fb_update();
	return;
}

static int pen_y = 30;
static void bluetooth_tty_event_cb(int fd)
{
	char buf[128];
	int n;
	n = myRead_nonblock(fd, buf, sizeof(buf) - 1);
	if (n <= 0)
	{
		// task_delete_file(fd);
		// close(fd);
		exit(0);
		return;
	}
	buf[n] = '\0';
	{
		int type, x, y, finger, weight, color;
		sscanf(buf, "%d %d %d %d %d %d", &type, &x, &y, &finger, &weight, &color);
		if (finger >= 0 && finger <= 4)
		{
			rec_color[finger] = color;
			switch (type)
			{
			case TOUCH_PRESS:
				rec_x_old[finger] = x, rec_y_old[finger] = y, rec_isPressing[finger] = 1;
				break;
			case TOUCH_MOVE:
				if (rec_isPressing[finger])
					fb_draw_line_weight(rec_x_old[finger], rec_y_old[finger], x, y, weight, rec_color[finger]);
				rec_x_old[finger] = x, rec_y_old[finger] = y;
				break;
			case TOUCH_RELEASE:
				rec_isPressing[finger] = 0;
				break;
			case TOUCH_ERROR:
				break;
			default:
				return;
			}
			fb_update();
		}
	}
	fb_update();
	pen_y += 30;
	return;
}

static int bluetooth_tty_init(const char *dev)
{
	int fd = open(dev, O_RDWR | O_NOCTTY | O_NONBLOCK); /*非阻塞模式*/
	if (fd < 0)
	{
		printf("bluetooth_tty_init open %s error(%d): %s\n", dev, errno, strerror(errno));
		return -1;
	}
	return fd;
}

// static int st = 0;
// static void timer_cb(int period) /*该函数0.5秒执行一次*/
// {
// 	char buf[100];
// 	sprintf(buf, "时间:%04d", st++);
// 	fb_draw_rect(TIME_X, TIME_Y, TIME_W, TIME_H, COLOR_BACKGROUND);
// 	fb_draw_border(TIME_X, TIME_Y, TIME_W, TIME_H, COLOR_TEXT);
// 	fb_draw_text(TIME_X + 10, TIME_Y + 30, buf, 24, COLOR_TEXT);
// 	fb_update();
// 	return;
// }

int main(int argc, char *argv[])
{
	color[0] = BLUE;
	color[1] = BLACK;
	color[2] = RED;
	color[3] = GREEN;
	color[4] = ORANGE;

	fb_init("/dev/fb0");
	font_init("./font.ttc");
	fb_draw_rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, COLOR_BACKGROUND);
	init();

	touch_fd = touch_init("/dev/input/event2");
	task_add_file(touch_fd, touch_event_cb);

	bluetooth_fd = bluetooth_tty_init("/dev/rfcomm0");
	if (bluetooth_fd == -1)
		return 0;
	task_add_file(bluetooth_fd, bluetooth_tty_event_cb);

	// task_add_timer(1000, timer_cb); /*增加0.5秒的定时器*/
	task_loop();
	return 0;
}
