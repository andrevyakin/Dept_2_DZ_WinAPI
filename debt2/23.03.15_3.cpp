/*3.	ўелчок правой кнопкой на клиентской области окна приводит к изменению его размеров (уменьшению в 2 раза).
Ќажатие любой клавиши возвращает исходные размеры*/

#include<Windows.h>
#include<stdlib.h>
#include<string>
#include<tchar.h>

static TCHAR WindowsClass[] = _T("win32app");
static TCHAR Title[] = _T("MyApp");
HINSTANCE hinst;

RECT desktop;
int X, Y, W, H; // координаты окна

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hinstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)

{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hinstance;
	wcex.hIcon = LoadIcon(hinstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	/*wcex.hbrBackground = CreateSolidBrush(RGB(100, 70, 150));*/
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = WindowsClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL, _T("Call faild!"), _T("MyApp"), NULL);
		return 1;
	}

	hinst = hinstance;

	//ѕолучить координаты рабочего стола
	GetWindowRect(GetDesktopWindow(), &desktop);

	X = desktop.right / 4;
	Y = desktop.bottom / 4;
	W = X * 2;
	H = Y * 2;



	HWND hWnd = CreateWindow(
		WindowsClass,
		Title,
		WS_OVERLAPPEDWINDOW,
		X,
		Y,
		W,
		H,
		NULL,
		NULL,
		hinst,
		NULL);

	if (!hWnd)
	{
		MessageBox(NULL, _T("Create window faild!"), _T("MyApp"), NULL);
		return 1;
	}

	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return(int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rect;
	RECT desktop;

	switch (message)
	{
	case WM_RBUTTONDOWN:
		SetWindowPos(hWnd, HWND_TOP, X*1.5, Y*1.5, W/2.5, H/2.5, SWP_SHOWWINDOW);
		break;
	case WM_KEYDOWN:
		SetWindowPos(hWnd, HWND_TOP, X, Y, W, H, SWP_SHOWWINDOW);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
}