#include <Windows.h>
#include <windowsx.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
VOID DrawFrame(HWND hwnd, POINT ptLeftTop, POINT ptRightBottom);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wndclass;
	TCHAR szClassName[] = TEXT("MyWindow");
	TCHAR szAppName[] = TEXT("DrawRectangle");
	HWND hwnd;
	MSG msg;

	wndclass.cbSize = sizeof(wndclass);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WindowProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_HAND);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szClassName;
	wndclass.hIconSm = NULL;

	RegisterClassEx(&wndclass);

	hwnd = CreateWindowEx(0, szClassName, szAppName, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 400, 300, NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0) != 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static POINT ptLeftTop, ptRightBottom;
	static BOOL bStarting;

	switch (uMsg)
	{
	case WM_LBUTTONDOWN:
		SetCursor(LoadCursor(NULL, IDC_CROSS));
		DrawFrame(hwnd, ptLeftTop, ptRightBottom);
		
		ptLeftTop.x = ptRightBottom.x = GET_X_LPARAM(lParam);
		ptLeftTop.y = ptRightBottom.y = GET_Y_LPARAM(lParam);

		bStarting = TRUE;

		return 0;
	case WM_MOUSEMOVE:
		if (bStarting)
		{
			SetCursor(LoadCursor(NULL, IDC_CROSS));
			DrawFrame(hwnd, ptLeftTop, ptRightBottom);

			ptRightBottom.x = GET_X_LPARAM(lParam);
			ptRightBottom.y = GET_Y_LPARAM(lParam);

			DrawFrame(hwnd, ptLeftTop, ptRightBottom);
		}

		return 0;
	case WM_LBUTTONUP:
		if (bStarting)
		{
			DrawFrame(hwnd, ptLeftTop, ptRightBottom);

			ptRightBottom.x = GET_X_LPARAM(lParam);
			ptRightBottom.y = GET_X_LPARAM(lParam);

			SetCursor(LoadCursor(NULL, IDC_ARROW));
			bStarting = FALSE;

			InvalidateRect(hwnd, NULL, TRUE);
		}

		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		Rectangle(hdc, ptLeftTop.x, ptLeftTop.y, ptRightBottom.x, ptRightBottom.y);
		EndPaint(hwnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

VOID DrawFrame(HWND hwnd, POINT ptLeftTop, POINT ptRightBottom)
{
	HDC hdc = GetDC(hwnd);
	SelectObject(hdc, GetStockObject(NULL_BRUSH));
	SetROP2(hdc, R2_NOT);
	Rectangle(hdc, ptLeftTop.x, ptLeftTop.y, ptRightBottom.x, ptRightBottom.y);
	SelectObject(hdc, GetStockObject(WHITE_BRUSH));
	ReleaseDC(hwnd, hdc);
}