#ifndef INCLUDE_JOYSTICK
#define INCLUDE_JOYSTICK

#include"lib_head.h"
#include "Input.h"

HRESULT InitJoyStick( HWND , LPDIRECTINPUT8& );

VOID FreeJoyStick();
HRESULT UpdateJoyStick( HWND );


//十字キー
enum CROSS_KEY{
	CROSS_UP,
	CROSS_RIGHT,
	CROSS_DOWN,
	CROSS_LEFT,
	CROSS_MAX,
};
//ボタン(XBox360)
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

//ボタン状態取得
//	pn：ジョイスティックの番号（何個目か）　b：調べたいボタンの定数
//	st：ボタンの状態
BOOL GetButton( int pn , BUTTON _b , eKEYSTATE _st);

//十字キーの入力状態
//	pn：ジョイスティックの番号（何個目か）　b：調べたい十字キー方向の定数
//	st：十字キーの状態	
BOOL GetCrossKey( int pn , CROSS_KEY _ck , eKEYSTATE _st );

#endif