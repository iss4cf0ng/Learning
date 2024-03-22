#include <Windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MessageBox(NULL, TEXT("Hello World!"), TEXT("Caption"), MB_OKCANCEL | MB_ICONINFORMATION | MB_DEFBUTTON2);
	return 0;
}