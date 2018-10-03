#include "lib_head.h"
#include "main.h"
#include "Window.h"

int CreateWindowProcess ( HINSTANCE hInst, HWND* hWnd )
{
	WNDCLASS winc;

	// Windows���̐ݒ�
	winc.style			= CS_HREDRAW | CS_VREDRAW; //�E�C���h�̃T�C�Y���ς�������ĕ`�悷�鏈��
	winc.lpfnWndProc	= WndProc;	// �����Ă������b�Z�[�W�����ɗl�X�ȏ������s���֐�
	winc.cbClsExtra		= winc.cbWndExtra = 0;
	winc.hInstance		= hInst;
	winc.hIcon			= LoadIcon( NULL, IDI_APPLICATION);
	winc.hCursor		= LoadCursor( NULL, IDC_ARROW);
	winc.hbrBackground	= (HBRUSH) GetStockObject (WHITE_BRUSH);
	winc.lpszMenuName	= NULL;
	winc.lpszClassName	= CLASS_NAME;

	// Windows�̓o�^
	if ( !RegisterClass (&winc))	return 0;

	// Windows�̐���
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
