#include <Windows.h>
#include <strsafe.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	TCHAR szName[] = TEXT("小明");
	TCHAR szAddress[] = TEXT("地球");
	int age = 18;
	TCHAR szBuf[128] = { 0 };
	HRESULT hResult = E_FAIL;

	hResult = StringCchPrintf(szBuf, _countof(szBuf), TEXT("我是%s，來自%s，年齡%d"), szName, szAddress, age);
	if (SUCCEEDED(hResult))
		MessageBox(NULL, szBuf, TEXT("格式化使用"), MB_OKCANCEL | MB_ICONINFORMATION);
	else
		MessageBox(NULL, TEXT("Failed"), TEXT("Error"), MB_OKCANCEL | MB_ICONWARNING);

	return 0;
}