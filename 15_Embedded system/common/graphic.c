#include "common.h"
#include <fcntl.h>
#include <linux/fb.h>
#include <linux/kd.h>
#include <linux/vt.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#define MIN(x, y) ((x) > (y) ? (y) : (x))
#define MAX(x, y) ((x) > (y) ? (x) : (y))
static int LCD_FB_FD;
static int *LCD_FB_BUF = NULL;
static int DRAW_BUF[SCREEN_WIDTH * SCREEN_HEIGHT];

static struct area
{
	int x1, x2, y1, y2;
} update_area = {0, 0, 0, 0};

#define AREA_SET_EMPTY(pa)        \
	do                            \
	{                             \
		(pa)->x1 = SCREEN_WIDTH;  \
		(pa)->x2 = 0;             \
		(pa)->y1 = SCREEN_HEIGHT; \
		(pa)->y2 = 0;             \
	} while (0)

void fb_init(char *dev)
{
	int fd;
	struct fb_fix_screeninfo fb_fix;
	struct fb_var_screeninfo fb_var;

	if (LCD_FB_BUF != NULL)
		return; /*already done*/

	//进入终端图形模式
	fd = open("/dev/tty0", O_RDWR, 0);
	ioctl(fd, KDSETMODE, KD_GRAPHICS);
	close(fd);

	// First: Open the device
	if ((fd = open(dev, O_RDWR)) < 0)
	{
		printf("Unable to open framebuffer %s, errno = %d\n", dev, errno);
		return;
	}
	if (ioctl(fd, FBIOGET_FSCREENINFO, &fb_fix) < 0)
	{
		printf("Unable to FBIOGET_FSCREENINFO %s\n", dev);
		return;
	}
	if (ioctl(fd, FBIOGET_VSCREENINFO, &fb_var) < 0)
	{
		printf("Unable to FBIOGET_VSCREENINFO %s\n", dev);
		return;
	}

	printf("framebuffer info: bits_per_pixel=%u,size=(%d,%d),virtual_pos_size=(%d,%d)(%d,%d),line_length=%u,smem_len=%u\n",
		   fb_var.bits_per_pixel, fb_var.xres, fb_var.yres, fb_var.xoffset, fb_var.yoffset,
		   fb_var.xres_virtual, fb_var.yres_virtual, fb_fix.line_length, fb_fix.smem_len);

	// Second: mmap
	void *addr = mmap(NULL, fb_fix.smem_len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (addr == (void *)-1)
	{
		printf("failed to mmap memory for framebuffer.\n");
		return;
	}

	if ((fb_var.xoffset != 0) || (fb_var.yoffset != 0))
	{
		fb_var.xoffset = 0;
		fb_var.yoffset = 0;
		if (ioctl(fd, FBIOPAN_DISPLAY, &fb_var) < 0)
		{
			printf("FBIOPAN_DISPLAY framebuffer failed\n");
		}
	}

	LCD_FB_FD = fd;
	LCD_FB_BUF = addr;

	// set empty
	AREA_SET_EMPTY(&update_area);
	return;
}

static void _copy_area(int *dst, int *src, struct area *pa)
{
	int x, y, w, h;
	x = pa->x1;
	w = pa->x2 - x;
	y = pa->y1;
	h = pa->y2 - y;
	src += y * SCREEN_WIDTH + x;
	dst += y * SCREEN_WIDTH + x;
	while (h-- > 0)
	{
		memcpy(dst, src, w * 4);
		src += SCREEN_WIDTH;
		dst += SCREEN_WIDTH;
	}
}

static int _check_area(struct area *pa)
{
	if (pa->x2 == 0)
		return 0; // is empty

	if (pa->x1 < 0)
		pa->x1 = 0;
	if (pa->x2 > SCREEN_WIDTH)
		pa->x2 = SCREEN_WIDTH;
	if (pa->y1 < 0)
		pa->y1 = 0;
	if (pa->y2 > SCREEN_HEIGHT)
		pa->y2 = SCREEN_HEIGHT;

	if ((pa->x2 > pa->x1) && (pa->y2 > pa->y1))
		return 1; // no empty

	// set empty
	AREA_SET_EMPTY(pa);
	return 0;
}

void fb_update(void)
{
	if (_check_area(&update_area) == 0)
		return; // is empty
	_copy_area(LCD_FB_BUF, DRAW_BUF, &update_area);
	AREA_SET_EMPTY(&update_area); // set empty
	return;
}

/*======================================================================*/

static void *_begin_draw(int x, int y, int w, int h)
{
	int x2 = x + w;
	int y2 = y + h;
	if (update_area.x1 > x)
		update_area.x1 = x;
	if (update_area.y1 > y)
		update_area.y1 = y;
	if (update_area.x2 < x2)
		update_area.x2 = x2;
	if (update_area.y2 < y2)
		update_area.y2 = y2;
	return DRAW_BUF;
}

void fb_draw_pixel(int x, int y, int color)
{
	if (x < 0 || y < 0 || x >= SCREEN_WIDTH || y >= SCREEN_HEIGHT)
		return;
	int *buf = _begin_draw(x, y, 1, 1);
	/*---------------------------------------------------*/
	*(buf + y * SCREEN_WIDTH + x) = color;
	/*---------------------------------------------------*/
	return;
}

void fb_draw_rect(int x, int y, int w, int h, int color)
{
	if (x < 0)
	{
		w += x;
		x = 0;
	}
	if (x + w > SCREEN_WIDTH)
	{
		w = SCREEN_WIDTH - x;
	}
	if (y < 0)
	{
		h += y;
		y = 0;
	}
	if (y + h > SCREEN_HEIGHT)
	{
		h = SCREEN_HEIGHT - y;
	}
	if (w <= 0 || h <= 0)
		return;
	//	int *buf = _begin_draw(x,y,w,h);
	/*---------------------------------------------------*/
	for (int i = y; i <= y + h; i++)
		for (int j = x; j <= x + w; j++)
			fb_draw_pixel(j, i, color);
	/*---------------------------------------------------*/
	return;
}

void fb_draw_line(int x1, int y1, int x2, int y2, int color)
{
	/*---------------------------------------------------*/
	int x = 0, y = 0;
	if (x1 == x2)
	{
		x = x1;
		for (y = MIN(y1, y2); y <= MAX(y1, y2); y++)
		{
			fb_draw_pixel(x, y, color);
		}
	}
	else
	{
		for (x = MIN(x1, x2); x <= MAX(x1, x2); x++)
		{
			y = (y2 - y1) * (x - x1) / (x2 - x1) + y1;
			fb_draw_pixel(x, y, color);
		}
		for (y = MIN(y1, y2); y <= MAX(y1, y2); y++)
		{
			x = (x2 - x1) * (y - y1) / (y2 - y1) + x1;
			fb_draw_pixel(x, y, color);
		}
	}
	/*---------------------------------------------------*/
	return;
}

void fb_draw_line_weight(int x1, int y1, int x2, int y2, int weight, int color)
{
	// int x = 0, y = 0;
	// if (x1 == x2)
	// {
	// 	x = x1;
	// 	for (y = MIN(y1, y2); y <= MAX(y1, y2); y++)
	// 	{
	// 		fb_draw_rect(x, y, weight, weight, color);
	// 	}
	// }
	// else
	// {
	// 	for (x = MIN(x1, x2); x <= MAX(x1, x2); x++)
	// 	{
	// 		y = (y2 - y1) * (x - x1) / (x2 - x1) + y1;
	// 		fb_draw_rect(x, y, weight, weight, color);
	// 	}
	// 	for (y = MIN(y1, y2); y <= MAX(y1, y2); y++)
	// 	{
	// 		x = (x2 - x1) * (y - y1) / (y2 - y1) + x1;
	// 		fb_draw_rect(x, y, weight, weight, color);
	// 	}
	// }
	int x = 0, y = 0;
	if (x1 == x2)
	{
		x = x1;
		for (y = MIN(y1, y2); y <= MAX(y1, y2); y++)
		{
			fb_draw_circle(x, y, weight, color);
		}
	}
	else
	{
		for (x = MIN(x1, x2); x <= MAX(x1, x2); x++)
		{
			y = (y2 - y1) * (x - x1) / (x2 - x1) + y1;
			fb_draw_circle(x, y, weight, color);
		}
		for (y = MIN(y1, y2); y <= MAX(y1, y2); y++)
		{
			x = (x2 - x1) * (y - y1) / (y2 - y1) + x1;
			fb_draw_circle(x, y, weight, color);
		}
	}
	return;
}

void fb_draw_circle(int cx, int cy, int radius, int color)
{
	int x, y, tmp;
	for (x = cx - radius; x <= cx + radius; x++)
	{
		tmp = sqrt(radius * radius - (x - cx) * (x - cx));
		y = cy + tmp;
		fb_draw_pixel(x, y, color);
		y = cy - tmp;
		fb_draw_pixel(x, y, color);
	}
	for (y = cy - radius; y <= cy + radius; y++)
	{
		tmp = sqrt(radius * radius - (y - cy) * (y - cy));
		x = cx + tmp;
		fb_draw_pixel(x, y, color);
		x = cx - tmp;
		fb_draw_pixel(x, y, color);
	}
}

void fb_draw_image(int x, int y, fb_image *image, int color)
{
	if (image == NULL)
		return;

	int ix = 0;				// image x
	int iy = 0;				// image y
	int w = image->pixel_w; // draw width
	int h = image->pixel_h; // draw height

	if (x < 0)
	{
		w += x;
		ix -= x;
		x = 0;
	}
	if (y < 0)
	{
		h += y;
		iy -= y;
		y = 0;
	}

	if (x + w > SCREEN_WIDTH)
	{
		w = SCREEN_WIDTH - x;
	}
	if (y + h > SCREEN_HEIGHT)
	{
		h = SCREEN_HEIGHT - y;
	}
	if ((w <= 0) || (h <= 0))
		return;

	int *buf = _begin_draw(x, y, w, h);
	/*---------------------------------------------------------------*/
	char *dst = (char *)(buf + y * SCREEN_WIDTH + x);
	char *src; //不同的图像颜色格式定位不同
			   /*---------------------------------------------------------------*/

	unsigned char alpha;
	unsigned char R1;
	unsigned char G1;
	unsigned char B1;
	if (image->color_type == FB_COLOR_RGB_8880) /*lab3: jpg*/
	{
		src = image->content;
		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w * 4; j++)
				dst[j] = src[j];
			src += w * 4;
			dst += SCREEN_WIDTH * 4;
		}
		return;
	}
	else if (image->color_type == FB_COLOR_RGBA_8888) /*lab3: png*/
	{
		src = image->content;
		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < image->line_byte; j += 4)
			{
				alpha = src[i * image->line_byte + j + 3];
				R1 = src[i * image->line_byte + j + 2];
				G1 = src[i * image->line_byte + j + 1];
				B1 = src[i * image->line_byte + j];
				switch (alpha)
				{
				case 0:
					break;
				case 255:
					dst[j] = B1;
					dst[j + 1] = G1;
					dst[j + 2] = R1;
				default:
					dst[j] += (((B1 - dst[j]) * alpha) >> 8);
					dst[j + 1] += (((G1 - dst[j + 1]) * alpha) >> 8);
					dst[j + 2] += (((R1 - dst[j + 2]) * alpha) >> 8);
				}
				dst[j + 3] = (char)0xff;
			}
			dst += SCREEN_WIDTH * 4;
		}
		return;
	}
	else if (image->color_type == FB_COLOR_ALPHA_8) /*lab3: font*/
	{
		src = image->content;
		R1 = color >> 16;
		G1 = color >> 8;
		B1 = color;
		for (int i = 0; i < image->pixel_h; i++)
		{
			for (int j = 0; j < image->line_byte; j++)
			{
				alpha = src[i * image->line_byte + j];
				switch (alpha)
				{
				case 0:
					break;
				default:
					dst[j * 4] = B1;
					dst[j * 4 + 1] = G1;
					dst[j * 4 + 2] = R1;
					dst[j * 4] += (((B1 - dst[j * 4]) * alpha) >> 8);
					dst[j * 4 + 1] += (((G1 - dst[j * 4 + 1]) * alpha) >> 8);
					dst[j * 4 + 2] += (((R1 - dst[j * 4 + 2]) * alpha) >> 8);
					dst[j * 4 + 3] = (char)0xff;
				}
			}
			dst += SCREEN_WIDTH * 4;
		}
		return;
	}
	/*---------------------------------------------------------------*/
	return;
}

void fb_draw_border(int x, int y, int w, int h, int color)
{
	if (w <= 0 || h <= 0)
		return;
	fb_draw_rect(x, y, w, 1, color);
	if (h > 1)
	{
		fb_draw_rect(x, y + h - 1, w, 1, color);
		fb_draw_rect(x, y + 1, 1, h - 2, color);
		if (w > 1)
			fb_draw_rect(x + w - 1, y + 1, 1, h - 2, color);
	}
}

/** draw a text string **/
void fb_draw_text(int x, int y, char *text, int font_size, int color)
{
	fb_image *img;
	fb_font_info info;
	int i = 0;
	int len = strlen(text);
	while (i < len)
	{
		img = fb_read_font_image(text + i, font_size, &info);
		if (img == NULL)
			break;
		fb_draw_image(x + info.left, y - info.top, img, color);
		fb_free_image(img);
		x += info.advance_x;
		i += info.bytes;
	}
	return;
}
