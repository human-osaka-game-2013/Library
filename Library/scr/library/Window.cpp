#include "lib_head.h"
#include "main.h"
#include "Window.h"

int CreateWindowProcess ( HINSTANCE hInst, HWND* hWnd )
{
	WNDCLASS winc;

	// Windows情報の設定
	winc.style			= CS_HREDRAW | CS_VREDRAW; //ウインドのサイズが変わった時再描画する処理
	winc.lpfnWndProc	= WndProc;	// 送られてきたメッセージを元に様々な処理を行う関数
	winc.cbClsExtra		= winc.cbWndExtra = 0;
	winc.hInstance		= hInst;
	winc.hIcon			= LoadIcon( NULL, IDI_APPLICATION);
	winc.hCursor		= LoadCursor( NULL, IDC_ARROW);
	winc.hbrBackground	= (HBRUSH) GetStockObject (WHITE_BRUSH);
	winc.lpszMenuName	= NULL;
	winc.lpszClassName	= CLASS_NAME;

	// Windowsの登録
	if ( !RegisterClass (&winc))	return 0;

	// Windowsの生成
	int dH = GetSystemMetrics (SM_CYCAPTION) + GetSystemMetrics (SM_CYFRAME) * 2;
	int dW = GetSystemMetrics (SM_CXFRAME) * 2;

	*hWnd = CreateWindow( CLASS_NAME,
						 TITLE,
						 WS_OVERLAPPEDWINDOW | WS_VISIBLE,
						 CW_USEDEFAULT,		// x
						 CW_USEDEFAULT,		// y
						 WIDTH + dW,			// Width
						 HEIGHT + dH,			// Height
						 NULL, NULL, hInst, NULL );

	return 1;
}
