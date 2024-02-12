#include <Windows.h>

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








