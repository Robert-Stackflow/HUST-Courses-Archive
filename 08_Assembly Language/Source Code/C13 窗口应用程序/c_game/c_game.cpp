// c_game.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "c_game.h"
#include <stdio.h>

#define MAX_LOADSTRING 100


struct BULLET//定义子弹结构体
{
	int x, y;
	bool exist;
};


HINSTANCE hInst;
HBITMAP bg, ship, bullet;
HDC        hdc, mdc, bufdc;
HWND    hWnd;
DWORD    tPre, tNow;
int        x, y, nowX, nowY;//光标坐标,飞机贴图坐标
int        w = 0, bcount;//w为滚动背景所要裁剪的宽度；记录飞机现有的子弹数目
BULLET  b[30];//存储飞机发出的子弹

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
void                MyPaint(HDC hdc);


int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nCmdShow)
{
	MSG msg;
	MyRegisterClass(hInstance);
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}
	do 
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			tNow = GetTickCount();
			if (tNow - tPre >= 40)
				MyPaint(hdc);
		}
	} while (msg.message != WM_QUIT);

	return msg.wParam;
}



ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wcex.lpfnWndProc = (WNDPROC)WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = NULL;
	wcex.hCursor = NULL;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName =_T("canvas");
	wcex.hIconSm = NULL;
	return RegisterClassEx(&wcex);
}


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HBITMAP bmp;
	POINT pt, lt, rb;
	RECT rect;
	hInst = hInstance;
	hWnd = CreateWindow(_T("canvas"), _T("绘图窗口"), WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
	if (!hWnd)
	{
		return FALSE;
	}

	MoveWindow(hWnd, 100, 100, 640, 480, true);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	hdc = GetDC(hWnd);
	mdc = CreateCompatibleDC(hdc);
	bufdc = CreateCompatibleDC(hdc);
	bmp = CreateCompatibleBitmap(hdc, 640, 480);
	SelectObject(mdc, bmp);

	bg = (HBITMAP)LoadImage(NULL, _T("bg.bmp"), IMAGE_BITMAP, 648, 480, LR_LOADFROMFILE);
	ship = (HBITMAP)LoadImage(NULL, _T("ship.bmp"), IMAGE_BITMAP, 100, 148, LR_LOADFROMFILE);
	bullet = (HBITMAP)LoadImage(NULL, _T("bullet.bmp"), IMAGE_BITMAP, 10, 20, LR_LOADFROMFILE);

	x = 300;
	y = 300;
	nowX = 300;
	nowY = 300;

	////设定鼠标光标位置
	pt.x = 300;
	pt.y = 300;
	ClientToScreen(hWnd, &pt);//把窗口坐标转化为屏幕坐标，因为SetCursorPos只认屏幕坐标
	SetCursorPos(pt.x, pt.y);
	ShowCursor(false);      //隐藏鼠标光标

	//限制鼠标光标移动区域
	GetClientRect(hWnd, &rect);//获取客户区窗口的大小
	lt.x = rect.left;
	lt.y = rect.top;
	rb.x = rect.right;
	rb.y = rect.bottom;
	ClientToScreen(hWnd, &lt);
	ClientToScreen(hWnd, &rb);
	rect.left = lt.x;
	rect.top = lt.y;
	rect.right = rb.x;
	rect.bottom = rb.y;
	ClipCursor(&rect);//限制鼠标在矩形区域内
	MyPaint(hdc);
	return TRUE;
}

void MyPaint(HDC hdc)
{
	char str[20] = "";
	LPCWSTR wszStr = new WCHAR[20];

	//LPCWSTR *str = new LPCWSTR[20];
	int i;
	SelectObject(bufdc, bg);
	BitBlt(mdc, 0, 0, w, 480, bufdc, 640 - w, 0, SRCCOPY);
	BitBlt(mdc, w, 0, 640 - w, 480, bufdc, 0, 0, SRCCOPY);

	//飞机贴图缓慢向鼠标移动
	if (nowX < x)
	{
		nowX += 10;
		if (nowX > x)
			nowX = x;
	}
	else
	{
		nowX -= 10;
		if (nowX < x)
			nowX = x;
	}

	if (nowY < y)
	{
		nowY += 10;
		if (nowY > y)
			nowY = y;
	}
	else
	{
		nowY -= 10;
		if (nowY < y)
			nowY = y;
	}


	SelectObject(bufdc, ship);
	BitBlt(mdc, nowX, nowY, 100, 74, bufdc, 0, 74, SRCAND);
	BitBlt(mdc, nowX, nowY, 100, 74, bufdc, 0, 0, SRCPAINT);
	SelectObject(bufdc, bullet);
	if (bcount != 0)
	for (i = 0; i<30; i++)
	if (b[i].exist)
	{
		BitBlt(mdc, b[i].x, b[i].y, 10, 10, bufdc, 0, 10, SRCAND);
		BitBlt(mdc, b[i].x, b[i].y, 10, 10, bufdc, 0, 0, SRCPAINT);
		b[i].x -= 10;
		if (b[i].x < 0)
		{
			bcount--;
			b[i].exist = false;
		}
	}

	sprintf_s(str, "X坐标%d    ", x);
	wszStr=LPCWSTR(str);

	TextOut(mdc, 0, 0, wszStr, strlen(str));
	sprintf_s(str, "Y坐标%d    ", y);
	
	TextOut(mdc, 0, 20, wszStr, strlen(str));
	BitBlt(hdc, 0, 0, 640, 480, mdc, 0, 0, SRCCOPY);
	tPre = GetTickCount();
	w += 10;
	if (w == 640)
		w = 0;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int i;
	switch (message)
	{
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)       //只要按下一次鼠标左键，都会从(nowX,nowY+30)出现一颗子弹
			PostQuitMessage(0);
		break;
	case WM_LBUTTONDOWN:
		for (i = 0; i<30; i++)
		{
			if (!b[i].exist)
			{
				b[i].x = nowX;
				b[i].y = nowY + 30;
				b[i].exist = true;
				bcount++;
				break;
			}
		}


	case WM_MOUSEMOVE:
		x = LOWORD(lParam);
		if (x > 530)
			x = 530;
		else if (x < 0)
			x = 0;

		y = HIWORD(lParam);
		if (y > 380)
			y = 380;
		else if (y < 0)
			y = 0;
		break;

	case WM_DESTROY:
		ClipCursor(NULL);
		DeleteDC(mdc);
		DeleteDC(bufdc);
		DeleteObject(bg);
		DeleteObject(bullet);
		DeleteObject(ship);
		ReleaseDC(hWnd, hdc);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}