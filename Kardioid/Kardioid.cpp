﻿#include<Windows.h>
#include<tchar.h>
#include<xstring>


typedef std::basic_string < TCHAR, std::char_traits<TCHAR>, std::allocator < TCHAR>> String;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
TCHAR WinName[] = _T("MainFrame");
int APIENTRY _tWinMain(HINSTANCE This, //Дескриптор текущего приложения
	HINSTANCE Prev, //В современных системах всегда 0
	LPTSTR cmd, //Командная строка
	int mode) //Режим отображения окна

{
	HWND hWnd; //Дескриптор главного окна программы
	MSG msg; //Структура для хранения сообщения
	WNDCLASS wc;//Класс окна
	//Определение класса окна
	wc.hInstance = This;
	wc.lpszClassName = WinName; //Имя класса окна
	wc.lpfnWndProc = WndProc; //Имя класса окна
	wc.style = CS_HREDRAW | CS_VREDRAW; //Стиль окна
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); //Стандартная иконка
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); //Стандартный курсор
	wc.lpszMenuName = NULL; //Нет меню
	wc.cbClsExtra = 0; //Нет дополнительных данных класса
	wc.cbWndExtra = 0; //Нет дополнительных данных окна
	//Заполнение окна белым цветом
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	if (!RegisterClass(&wc)) return 0;//Регистрация класса окна
	//Создание окна
	hWnd = CreateWindow(WinName,//Имя класса окна
		_T("Каркас Windows-приложения"),//Заголовок окна
		WS_OVERLAPPEDWINDOW, //Стиль окна
		CW_USEDEFAULT,//x
		CW_USEDEFAULT,//y Размеры окна
		CW_USEDEFAULT,//Width
		CW_USEDEFAULT,//Height
		HWND_DESKTOP,//Дескриптор родительской информации нет
		NULL,//Нет меню
		This,//Дескриптор приложения
		NULL);//Дополнительной информации нет
	ShowWindow(hWnd, mode);//Показать окно
	//Цикл обработки сообщений
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);//Функция трансляции кодов нажатой клавиши
		DispatchMessage(&msg);//Посылает сообщение функции WndProc()
	}
	return 0;

}
//Оконная функция вызывается операционной системой
//и получает сообщения из очереди для данного приложения
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	int a,b,x, y;
	static int sx, sy;
	double angle;
	//Обработчик сообщений
	switch (message)
	{
	case WM_SIZE:
		sx = LOWORD(lParam);
		sy = HIWORD(lParam);
		break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		a = sx / 2;
		b = sy / 2;
		MoveToEx(hdc, 0, b, NULL);
		LineTo(hdc, sx, b);
		MoveToEx(hdc, a, 0, NULL);
		LineTo(hdc, a, sy);
		MoveToEx(hdc, a, b, NULL);
		for (angle = 0.0; angle < 2 * 3.14; angle += 0.1) {
			x = a + 200 * (1 - cos(angle)) * cos(angle);
			y = b - 200 * (1 - cos(angle)) * sin(angle);
			LineTo(hdc, x, y);
		}
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY: PostQuitMessage(0);
		break;
	default: return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
