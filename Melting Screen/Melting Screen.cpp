﻿#include <Windows.h>

int Width, Height, interval = 100;

LRESULT CALLBACK Melt(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg)
	{
	case WM_CREATE:{
		HDC dsktp = GetDC(HWND_DESKTOP);
		HDC wnd = GetDC(hWnd);
		BitBlt(wnd, 0, 0, Width, Height, dsktp, 0, 0, SRCCOPY);
		ReleaseDC(hWnd, wnd);
		ReleaseDC(HWND_DESKTOP, dsktp);
		SetTimer(hWnd, 0, interval, 0);
		ShowWindow(hWnd, SW_SHOW);
		break;
	}
	case WM_PAINT: {
		ValidateRect(hWnd, 0);
		break;
	}
	case WM_TIMER: {
		HDC wndw = GetDC(hWnd);
		int x = (rand() % Width) - 100;
		int y = (rand() % 15);
		int width = (rand() % 200);
		BitBlt(wndw, x, y, width, Height, wndw, x, 0, SRCCOPY);
		ReleaseDC(hWnd, wndw);
		break;
	}
	case WM_DESTROY: {
		KillTimer(hWnd, 0);
		PostQuitMessage(0);
		break;
	}

	return 0;
	
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

int APIENTRY main(HINSTANCE inst, HINSTANCE prev, LPSTR cmd, int showCmd) {
	Width = GetSystemMetrics(SM_CXSCREEN);
	Height = GetSystemMetrics(SM_CYSCREEN);
	WNDCLASS wndClass = {0, Melt, 0, 0, inst, 0, LoadCursor(0, IDC_ARROW), 0, 0, L"ScreenMelting"};
	if (RegisterClass(&wndClass)) {
		HWND hWnd = CreateWindowExA(WS_EX_TOPMOST, "ScreenMelting", 0, WS_POPUP, 0, 0, Width, Height, HWND_DESKTOP, 0, inst, 0);
		if (hWnd) {
			srand(GetTickCount());
			MSG msg = { 0 };
			while (msg.message != WM_QUIT) {
				if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}
		}
	}
}







