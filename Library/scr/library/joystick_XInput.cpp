#include <Windows.h>
#include "joystick_XInput.h"

XINPUT_STATE CXInput::xCurrentkState;	//	XInputGetStateからの情報を受取る用
CXInput::STICK_STATE CXInput::StickState[XUSER_MAX_COUNT];	//	取得可能スティック分の配列

/*
	private
*/
//	コンストラクタ
CXInput::CXInput() 
{

}

//	ボタンのチェック
//	トリガー以外の状態更新（トリガーは0～255で押され具合も出るので）
//	@pragma	_user	何番目のスティックか
void CXInput::CheckButton( int _user )
{
	WORD wTemp = xCurrentkState.Gamepad.wButtons;

	for( int iType = 0; iType < STICK_TYPE_MAX; iType++ )
	{
		WORD wConst = 0;
		BYTE bTrigger = 0;
		eSTICK_STATE stTemp = StickState[_user].Button[iType];

		switch( iType )
		{
		case CROSS_UP:
			wConst = XINPUT_GAMEPAD_DPAD_UP;
			break;
		case CROSS_DOWN:
			wConst = XINPUT_GAMEPAD_DPAD_DOWN;
			break;
		case CROSS_LEFT:
			wConst = XINPUT_GAMEPAD_DPAD_LEFT;
			break;
		case CROSS_RIGHT:
			wConst = XINPUT_GAMEPAD_DPAD_RIGHT;
			break;
		
		case BUTTON_START:
			wConst = XINPUT_GAMEPAD_START;
			break;
		case BUTTON_BACK:
			wConst = XINPUT_GAMEPAD_BACK;
			break;
		
		case BUTTON_LEFT_THUMB:
			wConst = XINPUT_GAMEPAD_LEFT_THUMB;
			break;
		case BUTTON_RIGHT_THUMB:
			wConst = XINPUT_GAMEPAD_RIGHT_THUMB;			
			break;
		case BUTTON_LEFT_SHOULDER:
			wConst = XINPUT_GAMEPAD_LEFT_SHOULDER;			
			break;
		case BUTTON_RIGHT_SHOULDER:
			wConst = XINPUT_GAMEPAD_RIGHT_SHOULDER;				
			break;
		
		case BUTTON_A:
			wConst = XINPUT_GAMEPAD_A;				
			break;
		case BUTTON_B:
			wConst = XINPUT_GAMEPAD_B;				
			break;
		case BUTTON_X:
			wConst = XINPUT_GAMEPAD_X;				
			break;
		case BUTTON_Y:
			wConst = XINPUT_GAMEPAD_Y;				
			break;
		
		case L_TRIGGER:
			wConst = 0;
			bTrigger = xCurrentkState.Gamepad.bLeftTrigger;
			break;
		case R_TRIGGER:
			wConst = 0;
			bTrigger = xCurrentkState.Gamepad.bRightTrigger;
			break;
		}

		if( wTemp & wConst && iType < L_TRIGGER )
		{
			if( stTemp > ON )
				StickState[_user].Button[iType] = PUSH;
			else
				StickState[_user].Button[iType] = ON;
		}
		else if( iType >= L_TRIGGER && bTrigger > 0  )
		{
			if( stTemp )
				StickState[_user].Button[iType] = ON;
			else
				StickState[_user].Button[iType] = PUSH;
		}
		else
		{
			if( stTemp < RELEASE )
				StickState[_user].Button[iType] = RELEASE;
			else
				StickState[_user].Button[iType] = OFF;
		}
	}
}

//	トリガーのチェック
//	右左トリガーの傾き度合いからeSTICK_STATEで判断
//	@pragma	_user	何番目のスティックか
void CXInput::CheckTrigger( int _user )
{

}

//	左右スティックのチェック
//	段階的に状態を設定するかは検討中
//	@pragma	_user	何番目のスティックか
void CXInput::CheckLRStick( int _user )
{

}

/*
	public
*/
//	スティック情報配列の初期化
void CXInput::Initialize()
{
	for( int iUser = 0; iUser < XUSER_MAX_COUNT; iUser++ )
	{
		for( int iType = 0; iType < STICK_TYPE_MAX; iType++ )
			StickState[iUser].Button[iType] = OFF;
	}

	//	XINPUT_STATE型のはZeroMemoryで
	ZeroMemory( &xCurrentkState, sizeof(XINPUT_STATE) );
}

//	全スティック情報の更新
void CXInput::UpdateStick()
{
	DWORD dwResult;	//	XInputGetState関数の結果用

	for( int iStick = 0; iStick < XUSER_MAX_COUNT; iStick++ )
	{
		//	XINPUT_STATE型のはZeroMemoryで
		//ZeroMemory( &xCurrentkState, sizeof(XINPUT_STATE) );

		//	現在のスティック状態を取得
		dwResult = XInputGetState( iStick, &xCurrentkState );

		if( dwResult == ERROR_SUCCESS )	// スティックがつながっている
		{ 
			CheckButton( iStick );
			CheckTrigger( iStick );
			CheckLRStick( iStick );
		}
		else	// つながってない
		{
			
		}
	}
}

//	StickState配列内からスティックの状態をチェック
//	@pragma _user	プレイヤー番号（0～3）
//	@pragma	_type	ボタンの種類
//	@pragma _state	ボタンの状態
//	@return	true：スティックが指定した通りの状態、false：指定した状態と違った
bool CXInput::CheckStickState( int _user, eSTICK_TYPE _type, eSTICK_STATE _state )
{
	bool bCheckF = false;

	if( StickState[_user].Button[_type] == _state )
		bCheckF = true;

	return bCheckF;
}
