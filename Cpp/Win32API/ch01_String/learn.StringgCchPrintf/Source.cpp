#include <Windows.h>
#include <strsafe.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	TCHAR szName[] = TEXT("�p��");
	TCHAR szAddress[] = TEXT("�a�y");
	int age = 18;
	TCHAR szBuf[128] = { 0 };
	HRESULT hResult = E_FAIL;

	hResult = StringCchPrintf(szBuf, _countof(szBuf), TEXT("�ڬO%s�A�Ӧ�%s�A�~��%d"), szName, szAddress, age);
	if (SUCCEEDED(hResult))
		MessageBox(NULL, szBuf, TEXT("�榡�ƨϥ�"), MB_OKCANCEL | MB_ICONINFORMATION);
	else
		MessageBox(NULL, TEXT("Failed"), TEXT("Error"), MB_OKCANCEL | MB_ICONWARNING);

	return 0;
}