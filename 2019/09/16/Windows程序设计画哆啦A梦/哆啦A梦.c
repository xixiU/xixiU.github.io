#include <windows.h>
#include <math.h>

#define NUM    1000
#define TWOPI  (2 * 3.1415926)

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT("HelloWin");
	HWND         hwnd;
	MSG          msg;
	WNDCLASS     wndclass;

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(/*GRAY*/WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;

	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("This program requires Windows NT!"),
			szAppName, MB_ICONERROR);
		return 0;
	}

	RegisterClass(&wndclass);

	hwnd = CreateWindow(szAppName,                  // window class name
		TEXT("The Hello Program"), // window caption
		WS_OVERLAPPEDWINDOW,        // window style
		CW_USEDEFAULT,               // initial x position
		CW_USEDEFAULT,               // initial y position
		CW_USEDEFAULT,              // initial x size
		CW_USEDEFAULT,              // initial y size
		NULL,                       // parent window handle
		NULL,                       // window menu handle
		hInstance,                  // program instance handle
		NULL);                     // creation parameters

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static int cxClient, cyClient;
	HBRUSH hBrush;
	int i;
	POINT apt[NUM],
		leftHand[] = {
		cxClient / 2 - 60, cyClient / 2 - 20,
		cxClient / 2 - 100, cyClient / 2 + 10,
		cxClient / 2 - 100, cyClient / 2 + 30,
		cxClient / 2 - 60, cyClient / 2 + 10
	},
		rightHand[] = {
		cxClient / 2 + 60, cyClient / 2 - 20,
		cxClient / 2 + 100, cyClient / 2 + 10,
		cxClient / 2 + 100, cyClient / 2 + 30,
		cxClient / 2 + 60, cyClient / 2 + 10
	};

	switch (message)
	{
	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam) + 120;
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		Ellipse(hdc, cxClient / 2 - 70, cyClient / 2 + 55, cxClient / 2, cyClient / 2 + 85);      //脚
		Ellipse(hdc, cxClient / 2, cyClient / 2 + 55, cxClient / 2 + 70, cyClient / 2 + 85);

		hBrush = CreateSolidBrush(RGB(0,159,232));
		SelectObject(hdc, hBrush);

		//    Rectangle (hdc, cxClient / 2 - 60, cyClient / 2 - 60, cxClient / 2 +60, cyClient / 2 + 70);    //身体
		RoundRect(hdc, cxClient / 2 - 60, cyClient / 2 - 60, cxClient / 2 + 60, cyClient / 2 + 70, 50, 20);

		DeleteObject(hBrush);


		SelectObject(hdc, GetStockObject(WHITE_BRUSH));
		//肚子部分
		Ellipse(hdc, cxClient / 2 - 50, cyClient / 2 - 50, cxClient / 2 + 50, cyClient / 2 + 50);   

		hBrush = CreateSolidBrush(RGB(0, 159, 232));
		SelectObject(hdc, hBrush);
		//头部
		Ellipse(hdc, cxClient / 2 - 100, cyClient / 2 - 220, cxClient / 2 + 100, cyClient / 2 - 20); 
		DeleteObject(hBrush);

		SelectObject(hdc, GetStockObject(WHITE_BRUSH));

		Ellipse(hdc, cxClient / 2 - 85, cyClient / 2 - 170, cxClient / 2 + 85, cyClient / 2 - 20);  //脸部
		Ellipse(hdc, cxClient / 2 - 40, cyClient / 2 - 190, cxClient / 2, cyClient / 2 - 140);    //眼眶左
		Ellipse(hdc, cxClient / 2, cyClient / 2 - 190, cxClient / 2 + 40, cyClient / 2 - 140);      //眼眶右

		SelectObject(hdc, GetStockObject(BLACK_BRUSH));
		//眼睛左
		Ellipse(hdc, cxClient / 2 - 15, cyClient / 2 - 155, cxClient / 2 - 10, cyClient / 2 - 150); 
		//眼睛右
		Ellipse(hdc, cxClient / 2 + 10, cyClient / 2 - 155, cxClient / 2 + 15, cyClient / 2 - 150);

		DeleteObject(hBrush);

		hBrush = CreateSolidBrush(RGB(255, 0, 0));
		SelectObject(hdc, hBrush);
		//鼻子
		Ellipse(hdc, cxClient / 2 - 10, cyClient / 2 - 150, cxClient / 2 + 10, cyClient / 2 - 130);    

		MoveToEx(hdc, cxClient / 2, cyClient / 2 - 130, NULL);
		LineTo(hdc, cxClient / 2, cyClient / 2 - 60);

		MoveToEx(hdc, cxClient / 2 - 40, cyClient / 2 - 75, NULL);          //嘴
		for (i = 0; i < NUM / 2; i++)
		{
			apt[i].x = cxClient / 2 - 40 + i * 160 / NUM;
			apt[i].y = cyClient / 2 - 75 + (int)(30 * sin(TWOPI * i / NUM)) / 2;
			LineTo(hdc, apt[i].x, apt[i].y);
		}

		MoveToEx(hdc, cxClient / 2 - 60, cyClient / 2 - 140, NULL);        //胡须
		LineTo(hdc, cxClient / 2 - 20, cyClient / 2 - 120);

		MoveToEx(hdc, cxClient / 2 - 60, cyClient / 2 - 110, NULL);
		LineTo(hdc, cxClient / 2 - 20, cyClient / 2 - 110);

		MoveToEx(hdc, cxClient / 2 - 60, cyClient / 2 - 80, NULL);
		LineTo(hdc, cxClient / 2 - 20, cyClient / 2 - 100);

		MoveToEx(hdc, cxClient / 2 + 60, cyClient / 2 - 140, NULL);
		LineTo(hdc, cxClient / 2 + 20, cyClient / 2 - 120);

		MoveToEx(hdc, cxClient / 2 + 60, cyClient / 2 - 110, NULL);
		LineTo(hdc, cxClient / 2 + 20, cyClient / 2 - 110);

		MoveToEx(hdc, cxClient / 2 + 60, cyClient / 2 - 80, NULL);
		LineTo(hdc, cxClient / 2 + 20, cyClient / 2 - 100);

        //口袋
		SelectObject(hdc, GetStockObject(WHITE_BRUSH));

		Chord(hdc, cxClient / 2 - 40, cyClient / 2 - 40, cxClient / 2 + 40, cyClient / 2 + 40,
			cxClient / 2 - 40, cyClient / 2 + 10, cxClient / 2 + 40, cyClient / 2 + 10);



		hBrush = CreateSolidBrush(RGB(255, 0, 0));                //脖子上的套圈
		SelectObject(hdc, hBrush);

		RoundRect(hdc, cxClient / 2 - 70, cyClient / 2 - 40, cxClient / 2 + 70, cyClient / 2 - 20, 20, 20);

		DeleteObject(hBrush);

		hBrush = CreateSolidBrush(RGB(0, 159, 232));              //手臂
		SelectObject(hdc, hBrush);

		SetPolyFillMode(hdc, WINDING);
		Polygon(hdc, leftHand, 4);

		SetPolyFillMode(hdc, WINDING);
		Polygon(hdc, rightHand, 4);

		DeleteObject(hBrush);

        //手
		SelectObject(hdc, GetStockObject(WHITE_BRUSH));

		Ellipse(hdc, cxClient / 2 - 115, cyClient / 2 + 5, cxClient / 2 - 85, cyClient / 2 + 35);
		Ellipse(hdc, cxClient / 2 + 115, cyClient / 2 + 5, cxClient / 2 + 85, cyClient / 2 + 35);

		hBrush = CreateSolidBrush(RGB(250, 255, 150));              //铃铛
		SelectObject(hdc, hBrush);

		Ellipse(hdc, cxClient / 2 - 10, cyClient / 2 - 35, cxClient / 2 + 10, cyClient / 2 - 15);

		DeleteObject(hBrush);


		SelectObject(hdc, GetStockObject(BLACK_BRUSH));

		Ellipse(hdc, cxClient / 2 - 4, cyClient / 2 - 29, cxClient / 2 + 4, cyClient / 2 - 21);

		MoveToEx(hdc, cxClient / 2, cyClient / 2 - 25, NULL);
		LineTo(hdc, cxClient / 2, cyClient / 2 - 15);

		EndPaint(hwnd, &ps);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}
