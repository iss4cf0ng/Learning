#include <Windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	int nRet = MessageBox(NULL, TEXT("Hello World!"), TEXT("Caption"), MB_OKCANCEL | MB_ICONINFORMATION | MB_DEFBUTTON2);
	switch (nRet)
	{
	case IDOK:
		MessageBox(NULL, TEXT("User pressed OK"), TEXT("Caption"), MB_OK);
		break;
	case IDCANCEL:
		MessageBox(NULL, TEXT("User pressed Cancel"), TEXT("Caption"), MB_OK);
		break;
	}
	
	return 0;
}