#define _USE_MATH_DEFINE
#include<Windows.h>
#include<tchar.h>
#include <cmath>
const int WIDTH = 110;
const int HEIGHT = 400;
double a = 1;
double b = 3;
double c = 1;
double d = 2;


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	HWND hMainWnd;
	TCHAR szClassName[] = _T("MyClass");
	MSG msg;
	WNDCLASSEX wc;
	//Заполняем структуру класса окна
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szClassName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	//Регистрируем класс окна
	if (!RegisterClassExW(&wc)) {
		MessageBoxW(NULL, _T("Cannot registr class"), _T("Error"), MB_OK);
		return 0;
	}
	//Создаем основное окно приложения
	hMainWnd = CreateWindow(szClassName, _T("A Hello1 Application"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL,
		hInstance, NULL);

	if (!hMainWnd) {
		MessageBox(NULL, _T("Cannot create main window"), _T("Error"), MB_OK);
		return 0;
	}
	//Показываем окно
	ShowWindow(hMainWnd, nCmdShow);
	//UpdateWindow(hMainWnd);
	//Выполняем цикл обработки сообщений до закрытия окна
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
	return msg.wParam;



}
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam,

	LPARAM lParam) {
	HDC hDC;
	PAINTSTRUCT ps;
	static HPEN hpen1, hpen2;
	static int sx, sy;
	double x, y, t;


	switch (uMsg) {
	case WM_CREATE:
		hpen1 = CreatePen(PS_SOLID, 1, RGB(255, 215, 0));
		hpen2 = CreatePen(PS_SOLID, 1, RGB(154, 205, 50));
		break;
	case WM_SIZE:
		sx = LOWORD(lParam);
		sy = HIWORD(lParam);
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		SetMapMode(hDC, MM_ANISOTROPIC);
		SetWindowExtEx(hDC, 2 * WIDTH, 2 * HEIGHT, NULL);
		SetViewportExtEx(hDC, sx / 2, sy / 2, NULL);
		SetViewportOrgEx(hDC, sx / 2, sy / 2, NULL);
		SelectObject(hDC, hpen1);
		MoveToEx(hDC, WIDTH, 0, NULL);
		LineTo(hDC, -WIDTH, 0);
		MoveToEx(hDC, 0, HEIGHT, NULL);
		LineTo(hDC, 0, -HEIGHT);
		SelectObject(hDC, hpen2);
		MoveToEx(hDC, -WIDTH, 0, NULL);
		for (x = -200; x <= 200; x += 1.0f / 50)
		{
			y = a * pow(x, 3) - b * pow(x, 2) + c * x + d;
			LineTo(hDC, x, y * 100);
		}
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		DeleteObject(hpen1);
		DeleteObject(hpen2);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;

}