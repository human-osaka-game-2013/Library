#ifndef INCLUDE_JOYSTICK
#define INCLUDE_JOYSTICK

#include"lib_head.h"
#include "Input.h"

HRESULT InitJoyStick( HWND , LPDIRECTINPUT8& );

VOID FreeJoyStick();
HRESULT UpdateJoyStick( HWND );


//�\���L�[
enum CROSS_KEY{
	CROSS_UP,
	CROSS_RIGHT,
	CROSS_DOWN,
	CROSS_LEFT,
	CROSS_MAX,
};
//�{�^��(XBox360)
enum BUTTON{
	BUTTON_A,
	BUTTON_B,
	BUTTON_X,
	BUTTON_Y,
	BUTTON_LB,
	BUTTON_RB,
	BUTTON_SELECT,
	BUTTON_START,
	BUTTON_LEFT_STICK,
	BUTTON_RIGHT_STICK,
	BUTTON_MAX,
};

//�{�^����Ԏ擾
//	pn�F�W���C�X�e�B�b�N�̔ԍ��i���ڂ��j�@b�F���ׂ����{�^���̒萔
//	st�F�{�^���̏��
BOOL GetButton( int pn , BUTTON _b , eKEYSTATE _st);

//�\���L�[�̓��͏��
//	pn�F�W���C�X�e�B�b�N�̔ԍ��i���ڂ��j�@b�F���ׂ����\���L�[�����̒萔
//	st�F�\���L�[�̏��	
BOOL GetCrossKey( int pn , CROSS_KEY _ck , eKEYSTATE _st );

#endif