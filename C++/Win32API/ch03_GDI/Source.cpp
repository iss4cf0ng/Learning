#include <Windows.h>
#include <tchar.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wndclass;
	TCHAR szClassName[] = TEXT("MyWindow");
	TCHAR szAppName[] = TEXT("SystemMetrics");
	HWND hwnd;
	MSG msg;

	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WindowProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadIcon(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szClassName;
	wndclass.hIconSm = NULL;

	RegisterClassEx(&wndclass);

	hwnd = CreateWindowEx(0, szClassName, szAppName, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 300, 180, NULL, NULL, hInstance, NULL);
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
	TCHAR szText[] = TEXT("For displayed text, if the end of a string does not fit in the rectangle, it is truncated and ellipses are added. If a word that is not at the end of the string goes beyond the limits of the rectangle, it is truncated without ellipses.");
	DRAWTEXTPARAMS dtp = { sizeof(DRAWTEXTPARAMS) };
	dtp.iLeftMargin = 10;
	dtp.iRightMargin = 10;
	RECT rect;

	switch (uMsg)
	{
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		SetBkMode(hdc, TRANSPARENT);
		SetTextColor(hdc, RGB(0, 0, 255));
		GetClientRect(hwnd, &rect);
		DrawTextEx(hdc, szText, -1, &rect, DT_WORDBREAK, &dtp);
		EndPaint(hwnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}