﻿#include<Windows.h>
#include<tchar.h>
#include<xstring>
typedef std::basic_string<TCHAR, std::char_traits<TCHAR>, std::allocator<TCHAR>>String;


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
TCHAR WinName[] = _T("MainFrame");
TCHAR r_str[] = _T("нажата правая кнопка");
TCHAR l_str[] = _T("нажата левая кнопка");
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
LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam)

{


	//и обработчик сообщений 
	PAINTSTRUCT ps;

	HDC hdc;

	int x, y;

	static int sx, sy;
	switch (message)

	{
	case WM_SIZE:

		sx = LOWORD(lParam);

		sy = HIWORD(lParam);

		break;

	case WM_PAINT:

		hdc = BeginPaint(hWnd, &ps);

		for (x = 0; x < sx; x += sx / 10)

		{
			MoveToEx(hdc, x, 0, NULL);
			LineTo(hdc, x, sy);

		}
		for (y = 0; y < sy; y += sy / 10)
		{


			MoveToEx(hdc, 0, y, NULL); LineTo(hdc, sx, y);


		}


		EndPaint(hWnd, &ps);

		break;

	case WM_DESTROY:
		PostQuitMessage(0);

		break; // Завершение программы

  //и обработка сообщения по умолчанию 
	default: return DefWindowProc(hWnd, message, wParam, lParam);

	}

	return 0;
}