//Copyright (c) LeafCore
#include "stdafx.h"

#include <windows.h>
#include <math.h>

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
void draw(HDC, double, double, double, double);

LPCWSTR szClassName = TEXT("LeafCore");

int WINAPI WinMain(HINSTANCE hThisInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpszArgument,
	int nFunsterStil)

{
	HWND hwnd;
	MSG messages;
	WNDCLASSEX wincl;

	wincl.hInstance = hThisInstance;
	wincl.lpszClassName = szClassName;
	wincl.lpfnWndProc = WindowProcedure;
	wincl.style = CS_DBLCLKS;
	wincl.cbSize = sizeof(WNDCLASSEX);

	wincl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wincl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wincl.hCursor = LoadCursor(NULL, IDC_ARROW);
	wincl.lpszMenuName = NULL;
	wincl.cbClsExtra = 0;
	wincl.cbWndExtra = 0;
	wincl.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);

	if (!RegisterClassEx(&wincl))
		return 0;

	hwnd = CreateWindowEx(
		0,
		szClassName,
		szClassName,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		1024,
		768,
		HWND_DESKTOP,
		NULL,
		hThisInstance,
		NULL
	);

	ShowWindow(hwnd, nFunsterStil);

	while (GetMessage(&messages, NULL, 0, 0)) {
		TranslateMessage(&messages);
		DispatchMessage(&messages);
	}

	return messages.wParam;
}

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	switch (message) {
	case WM_PAINT:
	{
		hdc = BeginPaint(hwnd, &ps);
		HPEN green_pen = CreatePen(PS_SOLID, 1, RGB(0, 127, 0));
		HPEN old_pen = (HPEN)SelectObject(hdc, green_pen);

		draw(hdc, 200, 400, 600, 400);

		SelectObject(hdc, old_pen);
		DeleteObject(green_pen);
		EndPaint(hwnd, &ps);
		break;
	}

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}

	return 0;
}

void draw(HDC hdc, double start_x, double start_y, double end_x, double end_y)
{
	if (fabs(start_x - end_x) < 2 && fabs(start_y - end_y) < 2) {
		//递归出口
		return;
	}

	//左三分点
	int left_point_x = (int)((2 * start_x + end_x) / 3);
	int left_point_y = (int)((2 * start_y + end_y) / 3);

	//中间点
	int middle_point_x = (int)((start_x + end_x) / 2 - 0.2887*(start_y - end_y));
	int middle_point_y = (int)((start_y + end_y) / 2 + 0.2887*(start_x - end_x));

	//右三分点
	int right_point_x = (int)((start_x + 2 * end_x) / 3);
	int right_point_y = (int)((start_y + 2 * end_y) / 3);

	//画出起点至左三分点
	MoveToEx(hdc, (int)start_x, (int)start_y, 0);
	LineTo(hdc, left_point_x, left_point_y);

	//画出左三分点至中间点
	draw(hdc, left_point_x, left_point_y, middle_point_x, middle_point_y);

	//画出中间点至右三分点
	draw(hdc, middle_point_x, middle_point_y, right_point_x, right_point_y);

	//画出右三分点至终点
	MoveToEx(hdc, right_point_x, right_point_y, 0);
	LineTo(hdc, (int)end_x, (int)end_y);

	//休眠30毫秒
	Sleep(30);
}
